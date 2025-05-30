# Cloth Simulation

The project is simulating bunch of particles that are bind by force with each other forming a grid, and applying physics mechanism to:

- Drag the particle (`Left Mouse Click`)
- Tear binding force (`Right Mouse Click`)

These experience is simulating the physical phenomenon of a hanging cloth.

## Framework

The project is written with C++ and SFML framework. Check the following page for SFML documentation https://www.sfml-dev.org/

## Development guideline

Note: The program is written in with Mac OS machine, thus Windows guideline is not available yet.

### Pre-requisite

- Install Homebrew by following the documentation here: https://brew.sh/
- When Homebrew installation is complete you should be able to execute execute `brew -v`
- Install SFML with Homebrew by executing the following command. `brew install sfml`
- During installation, Homebrew may give information about required dependencies. Then follow the instruction to install those dependencies with homebrew.

### Development

- Run `brew info sfml` to confirm installation and grab the file path to sfml assets installed from homebrew
- Run `cp .env.example .env`, and replace the `SFML_PATH` value with the path you retrieved from the previous step.
- If running the code with VSCode run `cp .vscode/c_cpp_properties.example.json .vscode/c_cpp_properties.json` and replace `SFML_PATH` similar from previous step

### Running Simulation

- Execute `make clean && make && ./a.out`

### Demo
 
 ![demo](https://github.com/user-attachments/assets/831c7aed-439f-4d6a-872f-79c94261f716)
