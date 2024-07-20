inputs: {
  pkgs,
  stdenv,
  ...
}: let
  resources = ./resources.xml;
in
  stdenv.mkDerivation {
    pname = "MyGuiTools";
    version = "3.4.3";

    src = inputs.mygui;

    nativeBuildInputs = with pkgs; [cmake pkg-config];
    buildInputs = with pkgs; [SDL2 SDL2_image libtiff libwebp freetype libGL libGLU zlib];

    cmakeFlags = [
      "-DMYGUI_BUILD_TOOLS=ON"
      "-DMYGUI_BUILD_DEMOS=OFF"
      "-DMYGUI_BUILD_PLUGINS=OFF"
      "-DMYGUI_RENDERSYSTEM=7"
      "-DMYGUI_INSTALL_TOOLS=TRUE"
    ];
    postInstall = ''
      mkdir -p "$out/share/MyGuiTools"
      cp -r "$src/Media" "$out/share/MyGuiTools/"
      cp ${resources} $out/share/MyGuiTools/resources.xml
    '';
  }
