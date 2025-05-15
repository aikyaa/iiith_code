from pyaedt import Hfss
from pyaedt.modeler.primitive import Polyline
import numpy as np
import uuid

# Initialize HFSS
hfss = Hfss(specified_version="2023.2", non_graphical=False, new_desktop=True, solution_type="DrivenModal")

# Set units
hfss.modeler.units = "mm"

# Define materials (FR4 substrate)
hfss.modeler.materials.add_material("FR4", permittivity=4.4, loss_tangent=0.02)

# Substrate dimensions
substrate_length = 20  # mm
substrate_width = 10   # mm
substrate_height = 1.6 # mm

# Create substrate
substrate = hfss.modeler.create_box([0, 0, 0], [substrate_length, substrate_width, substrate_height], name="Substrate", material="FR4")

# Ground plane (copper, bottom of substrate)
ground = hfss.modeler.create_box([0, 0, 0], [substrate_length, substrate_width, 0.035], name="Ground", material="copper")

# IDC parameters
finger_length = 6      # mm
finger_width = 0.2     # mm
finger_spacing = 0.2   # mm
num_fingers = 8        # Even number for symmetry
electrode_width = 0.5  # mm
feed_width = 1.0       # mm for CPW feed

# Calculate total IDC width
idc_width = num_fingers * finger_width + (num_fingers - 1) * finger_spacing
idc_start_x = (substrate_length - idc_width) / 2
idc_start_y = (substrate_width - finger_length - 2 * electrode_width) / 2

# Create IDC electrodes and fingers
points_electrode1 = [
    [idc_start_x, idc_start_y, substrate_height],
    [idc_start_x + idc_width, idc_start_y, substrate_height],
    [idc_start_x + idc_width, idc_start_y + electrode_width, substrate_height],
    [idc_start_x, idc_start_y + electrode_width, substrate_height]
]
electrode1 = hfss.modeler.create_polyline(points_electrode1, close=True, name="Electrode1", material="copper")
electrode1.thickness = 0.035  # Copper thickness in mm

points_electrode2 = [
    [idc_start_x, idc_start_y + electrode_width + finger_length, substrate_height],
    [idc_start_x + idc_width, idc_start_y + electrode_width + finger_length, substrate_height],
    [idc_start_x + idc_width, idc_start_y + 2 * electrode_width + finger_length, substrate_height],
    [idc_start_x, idc_start_y + 2 * electrode_width + finger_length, substrate_height]
]
electrode2 = hfss.modeler.create_polyline(points_electrode2, close=True, name="Electrode2", material="copper")
electrode2.thickness = 0.035

# Create fingers
fingers = []
for i in range(num_fingers):
    x_start = idc_start_x + i * (finger_width + finger_spacing)
    if i % 2 == 0:  # Fingers from electrode1
        points = [
            [x_start, idc_start_y + electrode_width, substrate_height],
            [x_start, idc_start_y + electrode_width + finger_length, substrate_height],
            [x_start + finger_width, idc_start_y + electrode_width + finger_length, substrate_height],
            [x_start + finger_width, idc_start_y + electrode_width, substrate_height]
        ]
    else:  # Fingers from electrode2
        points = [
            [x_start, idc_start_y + electrode_width, substrate_height],
            [x_start, idc_start_y + 2 * electrode_width + finger_length, substrate_height],
            [x_start + finger_width, idc_start_y + 2 * electrode_width + finger_length, substrate_height],
            [x_start + finger_width, idc_start_y + electrode_width, substrate_height]
        ]
    finger = hfss.modeler.create_polyline(points, close=True, name=f"Finger{i}", material="copper")
    finger.thickness = 0.035
    fingers.append(finger)

# CPW feed lines
feed1 = hfss.modeler.create_box([0, idc_start_y + electrode_width - feed_width/2, substrate_height],
                               [idc_start_x, feed_width, 0.035], name="Feed1", material="copper")
feed2 = hfss.modeler.create_box([idc_start_x + idc_width, idc_start_y + electrode_width - feed_width/2, substrate_height],
                               [substrate_length - (idc_start_x + idc_width), feed_width, 0.035], name="Feed2", material="copper")

# Define lumped ports
port1 = hfss.modeler.create_rectangle(
    position=[0, idc_start_y + electrode_width - feed_width/2, substrate_height],
    dimension=[0, feed_width, 0.035],
    name="Port1"
)
hfss.assign_lumped_port("Port1", integration_line=[0, idc_start_y + electrode_width - feed_width/2, substrate_height,
                                                  0, idc_start_y + electrode_width + feed_width/2, substrate_height])

port2 = hfss.modeler.create_rectangle(
    position=[substrate_length, idc_start_y + electrode_width - feed_width/2, substrate_height],
    dimension=[0, feed_width, 0.035],
    name="Port2"
)
hfss.assign_lumped_port("Port2", integration_line=[substrate_length, idc_start_y + electrode_width - feed_width/2, substrate_height,
                                                  substrate_length, idc_start_y + electrode_width + feed_width/2, substrate_height])

# Air box for radiation boundary
air_box = hfss.modeler.create_box([0, 0, 0], [substrate_length, substrate_width, substrate_height + 10], name="AirBox", material="air")
hfss.assign_radiation_boundary_to_objects(["AirBox"])

# Setup analysis
setup = hfss.create_setup("Setup1")
setup.props["Frequency"] = "3GHz"
setup.props["MaximumPasses"] = 15
setup.props["MinimumConvergedPasses"] = 3
setup.props["MinimumDeltaS"] = 0.005

# Frequency sweep
sweep = setup.add_sweep("Sweep1", "Discrete")
sweep.props["RangeStart"] = "1GHz"
sweep.props["RangeEnd"] = "6GHz"
sweep.props["RangeCount"] = 101

# Sensitivity analysis: Simulate with material under test (MUT) with varying permittivity
# MUT is a thin layer above IDC
mut_height = 0.1  # mm
mut = hfss.modeler.create_box([idc_start_x, idc_start_y, substrate_height + 0.035],
                             [idc_width, finger_length + 2 * electrode_width, mut_height], name="MUT", material="vacuum")

# Define variable for MUT permittivity
hfss["eps_mut"] = "2"
mut.material = "dielectric"
mut.material_properties = {"Permittivity": "$eps_mut"}

# Create parametric sweep for sensitivity
parametric = hfss.create_parametric("Parametric1")
parametric.add_variation("eps_mut", start="2", stop="10", step="2")
parametric.analyze()

# Post-processing: Calculate sensitivity
# Sensitivity = |(f2 - f1)/f1| * 100%, where f1, f2 are resonant frequencies for different permittivities
hfss.post.create_report("S11_dB", "dB(S(1,1))", "Setup1:Sweep1", "Frequency")
hfss.post.create_report("S21_dB", "dB(S(2,1))", "Setup1:Sweep1", "Frequency")

# Save and analyze
hfss.save_project("IDC_Sensor.aedt")
hfss.analyze_all()

# Note: Sensitivity calculation requires extracting resonant frequencies from S11 minima
# This can be done post-simulation in HFSS or by exporting data and processing in Python

hfss.release_desktop()