self': {
  pkgs,
  stdenvNoCC,
  lib,
  ...
}: let
  script = pkgs.writeShellScript "launcher" ''
    mkdir -p /tmp/sm-gui-editor/
    ln -sf ${self'.packages.mygui}/share/MyGuiTools/resources.xml /tmp/sm-gui-editor/resources.xml
    ln -sf ${self'.packages.mygui}/share/MyGuiTools/Media /tmp/sm-gui-editor/Media
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
