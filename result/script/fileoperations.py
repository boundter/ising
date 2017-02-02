import csv
import numpy as np

# TODO: Clean up the reading of the header in ReadFile


def is_number(s):
    """
    Checks, if a string can be cast to float.

    @type s: string
    @param s: String, that will be checked.
    @rtype: bool
    @return: If the string can be cast to float.
    """
    try:
        float(s)
        return True
    except ValueError:
        return False


def ReadFile(filename, number_headers, delim):
    """
    Reads a csv-file and returns all header-values and file-entrys

    @type  filename: string
    @param filename: Name and path of the file
    @type  number_headers: number
    @param number_header: Number of lines, that contain the header
    @rtype:   tuple
    @return:  The first entry of the tuple is a list of all header values.
              The second entry contains a np.array of the data in the same
              order as the file
    """
    data = []
    value_dict = {}
    with open(filename, "r") as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=delim)
        for i in range(0, number_headers):
            header = csv_reader.__next__()
            for element in header:
                indx = header.index(element)
                if element != '' and element[-1] == '=' and\
                   indx < len(header) - 1 and is_number(header[indx + 1]):
                    key = element[:-1]
                    value = header[indx + 1]
                    value_dict[key] = float(value)
        for row in csv_reader:
            data.append([float(value) for value in row if value != ""])
    data = np.array(data, dtype=np.float64).transpose()
    return value_dict, data


def SplitData(indx, data):
    """
    Reads a continous numpy array [[keys], [value1], [value2], ...], where the
    keys specify a dataset and returns a list of separate numpy arrays.
    @type  indx: int
    @param indx: Index of the keys in the array
    @type  data: np.array
    @param data: Dataset of the specified form

    """
    unique, indices = np.unique(data[indx], return_index=True)
    data_trans = data.transpose()
    new_data = []
    old_pos = 0
    indices = np.append(indices[1:], data[indx].size)
    for pos in indices:
        new_data.append([])
        for i in range(old_pos, pos):
            new_data[-1].append([])
            for j in range(0, data_trans[i].size):
                if j != indx:
                    new_data[-1][-1].append(data_trans[i][j])
        old_pos = pos
    return_data = []
    for element in new_data:
        element = np.array(element, dtype=np.float64).transpose()
        return_data.append(element)
    return return_data
