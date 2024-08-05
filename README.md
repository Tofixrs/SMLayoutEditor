# SMLayoutEditor

MyGui layout editor for Scrap Mechanic packaged for the nix package manager

## cachix

```nix
{
  nix.settings = {
    substituters = ["https://sm-gui-editor.cachix.org"];
    trusted-public-keys = ["sm-gui-editor.cachix.org-1:sOHlz7KeslsRSBiGfE5G4Hbm7URIdtaI1zZSeL92m3s="];
  };
}
```

## Flatpak

0. Installing flatpak
   Refer to [this](https://flatpak.org/setup/)

1. Getting the flatpak

There are two sorces of the flatpak as of now (with flathub possibly being added as a 3rd option in the future):

- [Published releases (stable)](https://github.com/Tofixrs/sm_layout_editor/releases/latest)
  This one should be the one you install  
  It is a specifically tagged release that (should) have no bugs in it  
  To get this one go to the [latest](https://github.com/Tofixrs/sm_layout_editor/releases/latest) release and download `smlayouteditor.flatpak`
  Now proceed to the next Step
- [CI jobs (unstable)](https://github.com/Tofixrs/sm_layout_editor/actions/workflows/flatpak.yml)
  This source is for move advanced users
  While it is more up to date it might not work at all
  To get it go to the [latest ci run](https://github.com/Tofixrs/sm_layout_editor/actions/workflows/flatpak.yml) and download the artifact

2. Install

To install simply run this command in the terminal

```sh
flatpak install /path/to/flatpak/

```

3. Setting up the flatpak

The last thing we need to do is to give the flatpak acess to scrap mechanic installation
To do that simply run these commands

```sh
flatpak override --filesystem=/path/to/sm
flatpak override --env=SM_PATH=/path/to/sm

```

Now simply run the flatpak
