self': {
  pkgs,
  stdenvNoCC,
  lib,
  ...
}: let
  script = pkgs.writeShellScript "launcher" ''
    ln -sf $XDG_DATA_HOME/SM-GuiEditor /tmp/sm-gui-editor
    cd /tmp/sm-gui-editor
    ${lib.getExe self'.packages.configGen}
    ${self'.packages.mygui}/bin/LayoutEditor
  '';
in
  stdenvNoCC.mkDerivation {
    pname = "SM-GuiEditor";
    version = "0.6.0";
    phases = ["installPhase"];
    installPhase = ''
      mkdir -p "$out/bin"
      mkdir -p "$out/share/applications"

      cp ${script} "$out/bin/launcher.sh"
      cat <<INI > $out/share/applications/SMGuiEditor.desktop
      [Desktop Entry]
      Name=Scrap Mechanic Gui Editor
      Exec=$out/bin/launcher.sh %f
      Type=Application
      INI

    '';
  }
