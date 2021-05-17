import csv
# import pandas as pd
    
# solid_scrap_csv = pd.read_csv("input_data_ss.csv")


ss_rows = [] #store solid scrap info
ts_rows = [] #store turning scrap info

with open('input_data_ss.csv', mode ='r') as file:
    csvFile = csv.reader(file)
    fields = next(file)
    for row in csvFile:
        ss_rows.append(row)
row_count_ss = len(ss_rows)

with open('input_data_ts.csv', mode ='r') as file:
    csvFile = csv.reader(file)
    fields = next(file)
    for row in csvFile:
        ts_rows.append(row)
row_count_ts = len(ts_rows)


input_mats = []
for i in range(row_count_ts):
    Metal_Identification_ID = "M_" + str(i+1)
    input_mats.append(Metal_Identification_ID)
input_composition = {}
input_stock = {}

input_costs = {}
for row, metal_name in zip(ts_rows, input_mats):
    input_costs[str(metal_name)] = float(row[3].replace(',', ''))
    metal_composition = [float(row[10].replace(',', '').replace('%', ''))/100,float(row[12].replace(',', '').replace('%', ''))/100,float(row[14].replace(',', '').replace('%', ''))/100,float(row[16].replace(',', '').replace('%', ''))/100,float(row[18].replace(',', '').replace('%', ''))/100,float(row[20].replace(',', '').replace('%', ''))/100,float(row[22].replace(',', '').replace('%', ''))/100,float(row[24].replace(',', '').replace('%', ''))/100,float(row[26].replace(',', '').replace('%', ''))/100]
    input_composition[metal_name] = metal_composition    # list
    metal_available = str(row[9])
    input_stock[metal_name] = float(metal_available.replace(',', ''))   #str



row_count_ss_data = row_count_ss - 1
input_mats_ss = []
for i in range(row_count_ss_data):
    Metal_Identification_ID = "M_ss" + str(i+1)
    input_mats_ss.append(Metal_Identification_ID)


input_composition_ss = {}
input_stock_ss = {}
input_costs_ss = {}
for row, metal_name in zip(ss_rows, input_mats_ss):
    input_costs_ss[str(metal_name)] = float(row[3].replace(',', ''))
    metal_composition_ss = [float(row[10].replace(',', '').replace('%', ''))/100,float(row[12].replace(',', '').replace('%', ''))/100,float(row[14].replace(',', '').replace('%', ''))/100,float(row[16].replace(',', '').replace('%', ''))/100,float(row[18].replace(',', '').replace('%', ''))/100,float(row[20].replace(',', '').replace('%', ''))/100,float(row[22].replace(',', '').replace('%', ''))/100,float(row[24].replace(',', '').replace('%', ''))/100,float(row[26].replace(',', '').replace('%', ''))/100]
    input_composition_ss[metal_name] = metal_composition_ss    # list
    metal_available_ss= str(row[9])
    input_stock_ss[metal_name] = float(metal_available_ss.replace(',', ''))   #str

sum =0
for key, value in input_costs.items():
    sum += value
print(sum)