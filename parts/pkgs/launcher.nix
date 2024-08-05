self': {
  pkgs,
  stdenvNoCC,
  lib,
  ...
}: let
  script = pkgs.writeShellScript "launcher" ''
    ${lib.getExe self'.packages.configGen}
    cd ${self'.packages.mygui}/share/MYGUI
    ${self'.packages.mygui}/bin/LayoutEditor $@
  '';
in
  stdenvNoCC.mkDerivation {
    pname = "SM-GuiEditor";
    version = "1.0.0";
    phases = ["installPhase"];
    installPhase = ''
      mkdir -p "$out/bin"
      mkdir -p "$out/share/applications"

      cp ${script} "$out/bin/sm-gui-launcher"
      cat <<INI > $out/share/applications/SMGuiEditor.desktop
      [Desktop Entry]
      Name=Scrap Mechanic Gui Editor
      Exec=$out/bin/sm-gui-launcher %f
      Type=Application
      INI

    '';

    meta.mainProgram = "launcher.sh";
  }
