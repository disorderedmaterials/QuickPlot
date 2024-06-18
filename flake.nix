{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";
    future.url = "github:NixOS/nixpkgs/nixos-unstable";
    # qt-idaaas.url = "github:disorderedmaterials/qt-idaaas";
    nixGL-src.url = "github:guibou/nixGL";
    nixGL-src.flake = false;
  };
  outputs = { self, nixpkgs, future, flake-utils, bundlers, nixGL-src }:
    let

      version = "0.1";
      base_libs = pkgs: with pkgs; [ cmake ninja ];
      gui_libs = { pkgs, q }:
        with pkgs; [
          glib
          libGL.dev
          libglvnd
          libglvnd.dev
          q.qtbase
          q.qtbase.dev
          q.qt3d
          q.qtquick3d
          q.qtsvg
          q.wrapQtAppsHook
        ];
      check_libs = pkgs: with pkgs; [ gtest ];

    in flake-utils.lib.eachSystem [ "x86_64-linux" "aarch64-linux" ] (system:

      let
        pkgs = import nixpkgs { inherit system; };
        next = import future { inherit system; };
        nixGL = import nixGL-src { inherit pkgs; };
        qt = pkgs.qt6; # qt-idaaas.packages.${system};
      in {
        checks.quickPlot = self.packages.quickPlot;
        packages.quickPlot = pkgs.stdenv.mkDerivation ({
          version = "0.0.1";
          pname = "quickPlot";
          src = ./.;
          buildInputs = base_libs pkgs ++ check_libs pkgs ++ (gui_libs {
            inherit pkgs;
            q = qt;
          });
          doCheck = true;
        });
        devShells.default = pkgs.stdenv.mkDerivation {
          name = "mildred-shell";
          buildInputs = base_libs pkgs ++ gui_libs {
            inherit pkgs;
            q = qt;
          } ++ check_libs pkgs ++ (with pkgs; [
            (pkgs.clang-tools.override { llvmPackages = pkgs.llvmPackages_13; })
            ccache
            ccls
            cmake-format
            cmake-language-server
            distcc
            gdb
            next.git-cliff
            nixfmt
            valgrind
          ]);
          shellHook = ''
            export XDG_DATA_DIRS=$GSETTINGS_SCHEMAS_PATH:$XDG_DATA_DIRS
            export LIBGL_DRIVERS_PATH=${
              pkgs.lib.makeSearchPathOutput "lib" "lib/dri"
              [ pkgs.mesa.drivers ]
            }
            export LIBVA_DRIVERS_PATH=${
              pkgs.lib.makeSearchPathOutput "out" "lib/dri"
              [ pkgs.mesa.drivers ]
            }
            export __EGL_VENDOR_LIBRARY_FILENAMES=${pkgs.mesa.drivers}/share/glvnd/egl_vendor.d/50_mesa.json
            export LD_LIBRARY_PATH=${
              pkgs.lib.makeLibraryPath [ pkgs.mesa.drivers ]
            }:${
              pkgs.lib.makeSearchPathOutput "lib" "lib/vdpau" [ pkgs.libvdpau ]
            }:${
              pkgs.lib.makeLibraryPath [ pkgs.libglvnd ]
            }"''${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
            export QT_PLUGIN_PATH="${qt.qt3d}/lib/qt-6/plugins:${qt.qtsvg}/lib/qt-6/plugins:$QT_PLUGIN_PATH"
          '';
          QML_IMPORT_PATH =
            "${qt.qtdeclarative}/lib/qt-6/qml/:${qt.qt3d}/lib/qt-6/qml/:${qt.qtquick3d}/lib/qt-6/qml/";
        };

        apps = {
          default =
            flake-utils.lib.mkApp { drv = self.packages.${system}.library; };
        };

        packages = {
          library = pkgs.stdenv.mkDerivation ({
            inherit version;
            pname = "mildred";
            src = ./.;
            buildInputs = base_libs pkgs ++ (gui_libs {
              inherit pkgs;
              q = qt;
            });
            nativeBuildInputs = [ pkgs.wrapGAppsHook ];

            cmakeFlags = [ "-G Ninja -DBUILD_EXAMPLES:bool=true" ];
            installPhase = ''
              mkdir -p $out/bin
              mv ./$out/bin/groups $out/bin/
            '';

            meta = with pkgs.lib; {
              description = "Plot lib for 2D/3D";
              homepage = "https://github.com/disorderedmaterials/plot";
              license = licenses.gpl3;
              maintainers = with maintainers; [ rprospero ];
            };
          });

          singularity =
            nixpkgs.legacyPackages.${system}.singularity-tools.buildImage {
              name = "mildred-${version}";
              diskSize = 1024 * 250;
              memSize = 1024 * 2;
              contents = [ self.packages.${system}.library ];
              runScript = "${nixGL.nixGLIntel}/bin/nixGLIntel ${
                  self.packages.${system}.library
                }/bin/groups $@";
            };
        };
      });
}
