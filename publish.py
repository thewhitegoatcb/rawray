import pathlib
from zipfile import ZipFile

def write_zip_folder(zip, src_path, dst_path):
    src_path = pathlib.Path(src_path)
    dst_path = pathlib.PurePath(dst_path)

    for p in src_path.rglob("*"):
        if p.is_file():
            rel_path = p.relative_to(src_path)
            zip.write(p, dst_path / rel_path)

with ZipFile('./publish/publish.zip', 'w') as zip_object:
    write_zip_folder(zip_object, "./rawray_lua/", "rawray/")
    write_zip_folder(zip_object, "./scripts", "rawray/")
    zip_object.write("./x64/Release/rawray.dll", "rawray/plugins/rawray.dll")
