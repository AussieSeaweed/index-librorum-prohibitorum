#!/usr/bin/env python3

import argparse
import datetime
import json
import os
import pathlib
import shutil


def main():
    parser = argparse.ArgumentParser(description='populate dmoj solutions')
    parser.add_argument('path', type=str, help='path to dmoj data folder')
    args = parser.parse_args()

    src_dirpath = pathlib.Path(args.path)
    dest_dirpath = pathlib.Path('./dmoj')

    with open(src_dirpath / 'info.json') as file:
        info = json.load(file)

    src_filepaths = {filename.stem: src_dirpath / filename for filename in map(pathlib.Path, os.listdir(src_dirpath))}
    dest_filepaths = {}

    for id_, metadata in info.items():
        problem = metadata['problem']
        language = metadata['language']
        filename = ('Main' if 'JAVA' in language else 'main') + src_filepaths[id_].suffix
        filepath = pathlib.Path(f'./dmoj/{problem}') / filename

        dest_filepaths[id_] = filepath

    print(f'Moving {len(info)} files...')

    for id_ in sorted(info.keys(), key=int, reverse=True):
        src_filepath = src_filepaths[id_]
        dest_filepath = dest_filepaths[id_]

        if not os.path.exists(dest_filepath):
            os.makedirs(dest_filepath.parent, exist_ok=True)
            shutil.copy(src_filepath, dest_filepath)
    
    print('Done!')


if __name__ == '__main__':
    main()

