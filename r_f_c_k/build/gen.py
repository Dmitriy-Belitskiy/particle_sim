def generate_macro_file(filename="run_beam.mac", n_step=10):
    with open(filename, "w") as f:
        # Write the initial part of the macro
        f.write("""/control/verbose 0
/run/verbose 0
/event/verbose 0
/tracking/verbose 0
/run/printProgress 1000
/run/initialize

/gps/particle gamma
/gps/ene/mono 1460.8 keV
/gps/direction 0 1 0

/gps/pos/type Plane
/gps/pos/shape Square
/gps/pos/centre 0 -2 0 m
/gps/pos/halfx 0.004 m
/gps/pos/halfy 0.02 m
/gps/pos/rot1 1 0 0
/gps/pos/rot2 0 0 -1





/B5/detector/setPositionX 0
/B5/detector/setPositionY -1
/B5/detector/setPositionZ 0

""")
        
        # Loop over n values and append the repeated section
        for n in range(0, 91, n_step):
            f.write(f"/B5/detector/setRotX {n}\n")
            f.write("/run/initialize\n")
            f.write("/run/beamOn 1000000\n\n")
    
    print(f"Macro file '{filename}' generated successfully.")

# Example usage
generate_macro_file(n_step=2)
