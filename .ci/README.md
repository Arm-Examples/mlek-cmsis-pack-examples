# Continuous Integration (CI) Test for MLEK

  
Content of `.ci` Directory   | Description
:----------------------------|:-----------------
`vcpkg-configuration.json`   | Tool setup for the CI test.


## GitHub Action Workflows

The [GitHub Actions](https://docs.github.com/en/actions) in the directory `.github/workflows` are the scripts for the CI tests. These scripts contain detailed comments about each step that is executed. 

The Arm Machine Learning Example Kit uses the ARM compiler (AC6) toolchain. As such all workflows are using this compiler.

- `AVH-FVP-CI.yml` implements the *AVH build and execution test* that runs on [Arm Virtual Hardware - Fixed Virtual Platforms (AVH FVP)](https://arm-software.github.io/AVH/main/simulation/html/index.html) simulation models. The directory `FVP` contains configuration files for the FVP simulation models.

- `Hardware-CI.yml` implmentes the *Hardware build test* that runs on evaluation boards. The output of this build test is stored as artifacts and can be downloaded to the evaluation board for execution.
