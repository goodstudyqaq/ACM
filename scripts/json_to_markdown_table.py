# -*- coding: UTF-8 -*-

"""
将 json 文件转成 markdown 的 table, json 格式必须为 normalObject
"""


from typing import Any, List
from dataclasses import dataclass
import sys
import json


@dataclass
class NormalObject(object):
    head_name: str
    sub_head_name: str
    new_file_name: str

    field_name: List[dict]
    content: List[dict]


def work(obj: NormalObject):
    with open(obj.new_file_name, "w") as f:
        f.write('# {}\n'.format(obj.head_name))
        f.write('## {}\n'.format(obj.sub_head_name))

        field_name_val = [val['name'] for val in obj.field_name]
        field_str = '|' + '|'.join(field_name_val) + '|'
        f.write(field_str + '\n')
        field_len = len(obj.field_name)
        tmp = '|-' * field_len + '|'
        f.write(tmp + '\n')

        # write content

        for c in obj.content:
            line_str = "|"
            for field in obj.field_name:
                val = c.get(field['value'], "")
                line_str = line_str + str(val) + '|'

            f.write(line_str + '\n')


def main():
    json_path = sys.argv[1]
    print(json_path)

    with open(json_path) as f:
        data = json.load(f)
    obj = NormalObject(**data)
    work(obj)


if __name__ == "__main__":
    main()
