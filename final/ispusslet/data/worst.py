import os

def print_first_line_of_files(directory):
    worst=-1
    worstname=""
    for root, dirs, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            try:
                with open(file_path, 'r') as f:
                    first_line = f.readline().strip()
                    if not "ans" in file_path:
                        continue
                    if int(first_line)>worst:
                        worst=int(first_line)
                        worstname=file_path
            except Exception as e:
                print(f"Error reading {file_path}: {e}\n")
    print(worstname,":",worst)

# Provide the path to the directory you want to start from
directory_path = "secret/"

print_first_line_of_files(directory_path)
