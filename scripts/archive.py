import sys
import os
import shutil

def list_files1(filepath, filetype):
    paths = []
    for root, dirs, files in os.walk(filepath):
        for file in files:
            if file.lower().endswith(filetype.lower()):
                paths.append(os.path.join(root, file))
    return (paths)


def list_files2(filepath, filetype):
    paths = []
    for file_name in os.listdir(filepath):
        if file_name.endswith(filetype):
            paths.append(os.path.join(filepath, file_name))
    return paths


def main():
    dir_path = sys.argv[1]
    print(dir_path)
    exe_files = list_files1(dir_path, ".exe")
    print(exe_files)
    for f in exe_files:
        os.remove(f)

    cpp_files = list_files2(dir_path, ".cpp")
    print(cpp_files)

    for f in cpp_files:
        file_name = os.path.basename(f)
        file_name = file_name[0: -4]

        prefix = None
        suffix = None
        for idx in range(0, len(file_name)):
            if '0' <= file_name[idx] <= '9':
                continue
            else:
                prefix = file_name[0: idx]
                suffix = file_name[idx:]
                break
        print(prefix, suffix)

        code_dir_path = os.path.join(dir_path, prefix)
        print(code_dir_path)
        if not os.path.isdir(code_dir_path):
            os.mkdir(code_dir_path)

        file_name = suffix + ".cpp"
        file_path = os.path.join(code_dir_path, file_name)
        if not os.path.exists(file_path):
            shutil.copy(f, file_path)

        os.remove(f)



if __name__ == "__main__":
    main()
