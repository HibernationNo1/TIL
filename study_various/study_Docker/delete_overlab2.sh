#!/bin/bash

## container 의 모든 이름 추출
# Extract the names of all Docker containers
container_names=$(docker ps -a --format '{{.Names}}')

# Convert the names to a list format
container_list=()
while IFS= read -r name; do
    container_list+=("$name")
done <<< "$container_names"

# Print the list (optional)
echo "Container Names List:"
for name in "${container_list[@]}"; do
    echo "$name"
done

## dir_path에 있는 모든 dir 이름 추출
# Define the directory path
dir_path="/var/lib/docker/overlay2"

# Initialize an array to hold the directory names
dir_name_list=()

# Check if the directory exists
if [ -d "$dir_path" ]; then
  # List only the directory names and store them in the array
  for dir in "$dir_path"/*; do
    if [ -d "$dir" ]; then
      dir_name_list+=("$(basename "$dir")")
    fi
  done
else
  echo "Directory $dir_path does not exist."
  exit 1
fi

# Print the directory names
echo "Directory names in $dir_path:"
for name in "${dir_name_list[@]}"; do
  echo "$name"
done

## dir중 container와 한 번도 대응되지 않은 것을 list로 추출
# Initialize an array to hold directories for deletion
for_del_dir_list=()

# Inspect each container and search for directory names
for container in "${container_list[@]}"; do
  echo "Inspecting container: $container"
  inspect_output=$(docker inspect "$container")

  for dir_name in "${dir_name_list[@]}"; do
    if echo "$inspect_output" | grep -q "$dir_name"; then
      echo "Directory $dir_name is used by container $container"
    else
      # Check if dir_name is already marked for deletion
      if [[ ! " ${for_del_dir_list[@]} " =~ " ${dir_name} " ]]; then
        for_del_dir_list+=("$dir_name")
      fi
    fi
  done
done

# Print the directories marked for deletion
echo "Directories marked for deletion:"
for name in "${for_del_dir_list[@]}"; do
  echo "$name"
done

# ## 삭제할 dir을 삭제
# # Delete directories marked for deletion
# for name in "${for_del_dir_list[@]}"; do
#   dir_to_delete="$dir_path/$name"
#   if [ -d "$dir_to_delete" ]; then
#     echo "Deleting directory: $dir_to_delete"
#     rm -rf "$dir_to_delete"
#   else
#     echo "Directory $dir_to_delete does not exist."
#   fi
# done

# sudo bash delete_overlay2.sh
