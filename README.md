[![bugsplat-github-banner-basic-outline](https://user-images.githubusercontent.com/20464226/149019306-3186103c-5315-4dad-a499-4fd1df408475.png)](https://bugsplat.com)
<br/>
# <div align="center">BugSplat</div> 
### **<div align="center">Crash and error reporting built for busy developers.</div>**
<div align="center">
    <a href="https://twitter.com/BugSplatCo">
        <img alt="Follow @bugsplatco on Twitter" src="https://img.shields.io/twitter/follow/bugsplatco?label=Follow%20BugSplat&style=social">
    </a>
    <a href="https://discord.gg/K4KjjRV5ve">
        <img alt="Join BugSplat on Discord" src="https://img.shields.io/discord/664965194799251487?label=Join%20Discord&logo=Discord&style=social">
    </a>
</div>

## 👋 Introduction

MyUnrealCrasher is an Unreal Engine 5 project for testing BugSplat crash reporting. This repo has been pre-configured with the [BugSplat-Unreal](https://github.com/BugSplat-Git/bugsplat-unreal) editor plugin that allows you to configure crash reporting with only a few keystrokes. 

Before diving into this sample, please complete the following tasks:

* [Sign Up](https://app.bugsplat.com/v2/sign-up) as a new BugSplat user
* Complete the [Welcome](https://app.bugsplat.com/v2/welcome) workflow and make a note of your BugSplat database
* Generate a Client ID and Client Secret for symbol uploads on the [Integrations](https://app.bugsplat.com/v2/settings/database/integrations) page

## 🥾 Steps

The following guide assumes your project is targeting Windows, but these steps are applicable to other Desktop platforms as well. On Mobile platforms the BugSplat plugin will automatically configure crash reporting and symbol uploads.

1. Before you clone this repo make sure you have [git-lfs](https://git-lfs.github.com/) installed.
2. Clone this repo and the associated submodules. It's important that this repo is cloned with the `--recurse-submodules` flag so that the BugSplat-Unreal plugin is also downloaded:

```sh
git clone https://github.com/BugSplat-Git/my-unreal-crasher --recurse-submodules
```

3. Double click the `MyUnrealCrasher.uproject` file to open the project in the Unreal Editor. Depending on the Unreal Engine version you have installed you may need to open the project and close it a few times until it prompts you to rebuild both MyUnrealCrasher and BugSplat.
4. Once the project has been opened, click `Edit > Project Settings` and scroll to the `BugSplat` section under `Plugins`.
5. Fill in the values for `Database`, `Application`, `Version`, `User`, and `Password`
6. Click `Add Symbol Uploads`
7. Package your project
8. In the `BugSplat` section of `Project Settings` click `Update Game INI`
9. Select the directory that contains the `Windows` or `WindowsNoEditor` folder

Run your packaged game to generate a crash report. Navigate to the [Crashes](https://app.bugsplat.com/v2/crashes) page and click the link in the ID column to view the details of your crash

If you did everything correctly your result should look something like this

<img width="1711" alt="image" src="https://user-images.githubusercontent.com/2646053/181916918-159e6c3a-d11a-4751-81e3-d22f90037d09.png">

