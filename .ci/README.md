[![Version](https://img.shields.io/github/v/release/Arm-Examples/mlek-cmsis-pack-examples)](https://github.com/Arm-Examples/mlek-cmsis-pack-examples/releases/latest)

# Example projects based on Arm ML (Machine Learning) evaluation kit

The provided **mlek-cmsis-pack-examples** are designed to work with the ARM compiler toolchain.

## Repository top-level structure

Directory                   | Description
:---------------------------|:--------------
[.ci](./)                                                                                                  | Includes the tool configuration for the **[GitHub Actions](#github-actions)** and the current description.
[.github/workflows](./../.github/workflows)                                                                | **[GitHub Actions](#github-actions)** .
[FVP/](./../FVP)                                                                                           | Configuration files for the **AVH FVP** simulation models.
[device/](./../device)                                                                                     | Device specific files.
[resources/](./../resources)                                                                               | Prerecorded sample data used in **object-detection** and **kws** (key word spotting) example projects.
[object-detection/](./../object-detection)                                                                 | Example project for **object-detection**.
[kws/](./../kws)                                                                                           | Example project for **kws** (key word spotting).
[docs/](./../docs)                                                                                         | Documentation files.
[common/](./../common)                                                                                     | Common files and platform-agnostic components for examples based on **[Arm ML Embedded evaluation kit](https://review.mlplatform.org/plugins/gitiles/ml/ethos-u/ml-embedded-evaluation-kit/)**.

## Projects and targets

This repository contains two **projects**

Project file                | Description
:---------------------------|:--------------
[./kws/kws.cproject.yml](./../kws/kws.cproject.yml)                                                       | Example project for **kws** (key word spotting). The application will detect a keyword in a sample audio file [sample_audio](./../resources/sample_audio.wav).
[./object-detection/object-detection.cproject.yml](./../object-detection/object-detection.cproject.yml)   | Example project for **object-detection**. The application will detect two objects in the sample image file [sample_image](./../resources/sample_image.png).

The following **targets** are supported respectively implementation is ongoing

Project name                                                               | Target               | Note
:--------------------------------------------------------------------------|:---------------------|:--------------
[`kws`](./../kws/kws.cproject.yml)                                         | `FRDM-K64F`          |
[`kws`](./../kws/kws.cproject.yml)                                         | `STM32F746-DISCO`    |
[`kws`](./../kws/kws.cproject.yml)                                         | `Alif-E7-M55-HP`     | Not implemented yet
[`kws`](./../kws/kws.cproject.yml)                                         | `AVH-SSE-300`        |
[`kws`](./../kws/kws.cproject.yml)                                         | `AVH-SSE-300-U55`    |
[`kws`](./../kws/kws.cproject.yml)                                         | `AVH-SSE-300-U65`    |
[`kws`](./../kws/kws.cproject.yml)                                         | `AVH-SSE-310`        |
[`kws`](./../kws/kws.cproject.yml)                                         | `AVH-SSE-310-U55`    |
[`kws`](./../kws/kws.cproject.yml)                                         | `AVH-SSE-310-U65`    |
[`object-detection`](./../object-detection/object-detection.cproject.yml)  | `AVH-SSE-300`        |
[`object-detection`](./../object-detection/object-detection.cproject.yml)  | `AVH-SSE-300-U55`    |
[`object-detection`](./../object-detection/object-detection.cproject.yml)  | `AVH-SSE-300-U65`    |
[`object-detection`](./../object-detection/object-detection.cproject.yml)  | `AVH-SSE-310`        |
[`object-detection`](./../object-detection/object-detection.cproject.yml)  | `AVH-SSE-310-U55`    |
[`object-detection`](./../object-detection/object-detection.cproject.yml)  | `AVH-SSE-310-U65`    |
[`object-detection`](./../object-detection/object-detection.cproject.yml)  | `Alif-E7-M55-HP`     | Not implemented yet

## GitHub Actions

The repository uses GitHub Actions to build and execute the ml examples:
Workflow                    | Description
:---------------------------|:--------------
[`.github/workflows/AVH-FVP-CI.yml`](./../.github/workflows/AVH-FVP-CI.yml)     | builds the examples for **AVH** targets and execute them.
[`.github/workflows/Hardware-CI.yml`](./../.github/workflows/Hardware-CI.yml)   | builds the examples for hardware targets and upload them as Artifacts.

Both workflows are executed periodically once a week, manually, and in case of push or pull operations.

## License

The examples are licensed under [![License](https://img.shields.io/github/license/Arm-Examples/mlek-cmsis-pack-examples?label)](https://github.com/Arm-Examples/mlek-cmsis-pack-examples/blob/main/LICENSE).

## Issues

Please feel free to raise an [issue on GitHub](https://github.com/Arm-Examples/mlek-cmsis-pack-examples/issues)
to report misbehavior (i.e. bugs) or start discussions about enhancements. This
is your best way to interact directly with the maintenance team and the community.
We encourage you to append implementation suggestions as this helps to decrease the
workload of the maintenance team.
