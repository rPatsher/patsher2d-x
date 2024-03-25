# 


import os
import os.path
import subprocess
import glob
import platform
import shutil
import tempfile
import uuid

def make_build_editor_sources(src_list):
    for file_path in src_list:
        directory = os.path.dirname(file_path)
        file_name = os.path.splitext(os.path.basename(file_path))[0]
        output_executable = os.path.join(directory, file_name)
        command = f"g++ {file_path} -o {output_executable}"
        try:
            result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            print(f"Build output for {file_path}:")
            print(result.stdout)

            if result.stderr:
                print(f"Build error for {file_path}:")
                print(result.stderr)

            print(f"Build successful. Executable created: {output_executable}\n")
        except subprocess.CalledProcessError as e:
            print(f"Build failed for {file_path} with error:\n{e}\n")


def make_editor_header_sources(header_list):
    for header_file in header_list:
        print(f"Processing header file: {header_file}")

        with open(header_file, 'r') as file:
            header_content = file.read()
            print(f"Header file content:\n{header_content}")
   	pass
            
def add_source_file(src_list, source_pattern):
    matching_files = []
    for pattern in src_list:
        matching_files.extend(glob.glob(pattern))

    return matching_files

def remove_editor_sources_file(src_list, files_to_remove):
    for file_to_remove in files_to_remove:
        if file_to_remove in src_list:
            src_list.remove(file_to_remove)
            print(f"Removed {file_to_remove} from the source list.")
        else:
            print(f"{file_to_remove} not found in the source list.")


def make_editor_icon_map(png_files):
    icon_map = {}

    for png_file in png_files:
        file_name = os.path.splitext(os.path.basename(png_file))[0]
        icon_map[file_name] = png_file

    return icon_map         


if __name__ == "__main__":

	
	editor_sources : list = []
	  
	
	# Debugger 
	
	editor_sources.Append("debug/editor_debugger.cpp")
	editor_sources.Append("debug/editor_profiler.cpp")
	
	# Export 
	
	editor_sources.Append("export/editor_export.cpp")
	editor_sources.Append("export/project_export.cpp")
	
	# GUI
	editor_sources.Append("gui/editor_scene_tabs.cpp")
	editor_sources.Append("gui/editor_scene_tree.cpp")
	editor_sources.Append("gui/editor_sub_viewport.cpp")
	editor_sources.Append("gui/editor_file_dialog.cpp")
	editor_sources.Append("gui/editor_debugger_tab.cpp")
	editor_sources.Append("gui/editor_insprector.cpp")
	
	# Sources
	editor_sources.Append("editor_scale.cpp")
	editor_sources.Append("editor_settings.cpp")
	editor_sources.Append("editor_property.cpp")
	editor_sources.Append("editor_interface.cpp")
	editor_sources.Append("editor_selected_map.cpp")
	editor_sources.Append("editor_map.cpp")
	editor_sources.Append("editor_log.cpp")
	editor_sources.Append("editor_data.cpp")
	
	
	
	
	
	
	