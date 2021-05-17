import csv
from decimal import *
getcontext().prec = 9  #setting precision to 9 values
# Import the PuLP lib
from pulp import *

fields = []
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




request_quantity_ts = 500
request_quantity_ss = 100

Cr_min = 0.120
Cr_max = 0.220

Ni_min = 0.030
Ni_max = 0.130

Mo_min = 0.000
Mo_max = 0.005

Cu_min = 0.000
Cu_max = 0.006

Sn_min = 0.000
Sn_max = 0.0003

Pb_min = 0.000
Pb_max = 0.0003

Co_min = 0.000
Co_max = 0.002

S_min = 0.000
S_max = 0.0003

P_min = 0.000
P_max = 0.0004

# Create the problem variable
prob_ts = LpProblem ("MinimiserLpAlliage", LpMinimize)

# Problem Data
row_count_ts_data = row_count_ts - 1
input_mats_ts = []
for i in range(row_count_ts_data):
    Metal_Identification_ID = "M_ts" + str(i+1)
    input_mats_ts.append(Metal_Identification_ID)

input_costs_ts = {}
for row, metal_name in zip(ts_rows, input_mats_ts):
    input_costs_ts[str(metal_name)] = float(row[3].replace(',', '').replace('%', ''))

input_composition_ts = {}
for row, metal_name in zip(ts_rows,input_mats_ts):
    metal_composition_ts = [float(Decimal(row[10].replace(',', '').replace('%', ''))/100),float(Decimal(row[12].replace(',', '').replace('%', ''))/100),float(Decimal(row[14].replace(',', '').replace('%', ''))/100),float(Decimal(row[16].replace(',', '').replace('%', ''))/100),float(Decimal(row[18].replace(',', '').replace('%', ''))/100),float(Decimal(row[20].replace(',', '').replace('%', ''))/100),float(Decimal(row[22].replace(',', '').replace('%', ''))/100),float(Decimal(row[24].replace(',', '').replace('%', ''))/100),float(Decimal(row[26].replace(',', '').replace('%', ''))/100)]
    input_composition_ts[metal_name] = metal_composition_ts

input_stock_ts = {}
for row, metal_name in zip(ts_rows,input_mats_ts):
    metal_available_ts = row[9]
    input_stock_ts[metal_name] = float(metal_available_ts.replace(',', '').replace('%', ''))


# Problem variables - amount in kg of each input
x_ts = LpVariable.dicts("input_mat", input_mats_ts, 0)

# The objective function is to minimize the total cost of the alloys  for a given quantity in KGS
prob_ts += lpSum([input_costs_ts[i]*x_ts[i] for i in input_mats_ts]), "AlliageCost"

# Quantity constraint in KGS.
prob_ts += lpSum([x_ts[i] for i in input_mats_ts]) == request_quantity_ts, "RequestedQuantity"

# MIN/MAX constraint of Cr in resultant Alloy
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][0] for i in input_mats_ts]) >= Cr_min*request_quantity_ts, "MinCr"
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][0] for i in input_mats_ts]) <= Cr_max*request_quantity_ts, "MaxCr"

# MIN/MAX constraints of cromium in resultant Alloy
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][1] for i in input_mats_ts]) >= Ni_min*request_quantity_ts, "MinNi"
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][1] for i in input_mats_ts]) <= Ni_max*request_quantity_ts, "MaxNi"

# MIN/MAX constraints of Mo in resultant Alloy
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][2] for i in input_mats_ts]) >= Mo_min*request_quantity_ts, "MinMo"
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][2] for i in input_mats_ts]) <= Mo_max*request_quantity_ts, "MaxMo"

# MIN/MAX constraints of Cu in resultant Alloy
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][3] for i in input_mats_ts]) >= Cu_min*request_quantity_ts, "MinCu"
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][3] for i in input_mats_ts]) <= Cu_max*request_quantity_ts, "MaxCu"

# MIN/MAX constraints of Sn in resultant Alloy
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][4] for i in input_mats_ts]) >= Sn_min*request_quantity_ts, "MinSn"
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][4] for i in input_mats_ts]) <= Sn_max*request_quantity_ts, "MaxSn"

# MIN/MAX constraints of Pb in resultant Alloy
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][5] for i in input_mats_ts]) >= Pb_min*request_quantity_ts, "MinPb"
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][5] for i in input_mats_ts]) <= Pb_max*request_quantity_ts, "MaxPb"

# MIN/MAX constraints of Co in resultant Alloy
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][6] for i in input_mats_ts]) >= Co_min*request_quantity_ts, "MinCo"
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][6] for i in input_mats_ts]) <= Co_max*request_quantity_ts, "MaxCo"

# MIN/MAX constraints of S in resultant Alloy
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][7] for i in input_mats_ts]) >= S_min*request_quantity_ts, "MinS"
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][7] for i in input_mats_ts]) <= S_max*request_quantity_ts, "MaxS"

# MIN/MAX constraints of P in resultant Alloy
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][8] for i in input_mats_ts]) >= P_min*request_quantity_ts, "MinP"
prob_ts += lpSum([x_ts[i]*input_composition_ts[i][8] for i in input_mats_ts]) <= P_max*request_quantity_ts, "MaxP"



# MAX constraints of available stock
for i in input_mats_ts:
    prob_ts += x_ts[i] <= input_stock_ts[i], ("MaxStock_" + i)

# Solve the problem
prob_ts.solve()

# The status of the solution
print ("Status:", LpStatus [prob_ts.status])

# Dislay the optimums of each var
for v in prob_ts.variables ():
    print (v.name, "=", v.varValue)

# Display metal compositions
Cr_value = sum([x_ts[i].varValue*input_composition_ts[i][0] for i in input_mats_ts])/request_quantity_ts
Ni_value = sum([x_ts[i].varValue*input_composition_ts[i][1] for i in input_mats_ts])/request_quantity_ts
Mo_value = sum([x_ts[i].varValue*input_composition_ts[i][2] for i in input_mats_ts])/request_quantity_ts
Cu_value = sum([x_ts[i].varValue*input_composition_ts[i][3] for i in input_mats_ts])/request_quantity_ts
Sn_value = sum([x_ts[i].varValue*input_composition_ts[i][4] for i in input_mats_ts])/request_quantity_ts
Pb_value = sum([x_ts[i].varValue*input_composition_ts[i][5] for i in input_mats_ts])/request_quantity_ts
Co_value = sum([x_ts[i].varValue*input_composition_ts[i][6] for i in input_mats_ts])/request_quantity_ts
S_value = sum([x_ts[i].varValue*input_composition_ts[i][7] for i in input_mats_ts])/request_quantity_ts
P_value = sum([x_ts[i].varValue*input_composition_ts[i][8] for i in input_mats_ts])/request_quantity_ts

print ("Cr content: " + str(Cr_value))
print ("Ni content: " + str(Ni_value))
print ("Mo content: " + str(Mo_value))
print ("Cu content: " + str(Cu_value))
print ("Sn content: " + str(Sn_value))
print ("Pb content: " + str(Pb_value))
print ("Co content: " + str(Co_value))
print ("S content: " + str(S_value))
print ("P content: " + str(P_value))

# The result of the objective function is here
print ("Total", value (prob_ts.objective))














#Reapeating above process for solid scrap


# Create the problem variable
prob_ss = LpProblem ("MinimiserLpAlliage", LpMinimize)

#same steps as above(compressed) but for solid scrap
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
    metal_composition_ss = [float(Decimal(row[10].replace(',', '').replace('%', ''))/100),float(Decimal(row[12].replace(',', '').replace('%', ''))/100),float(Decimal(row[14].replace(',', '').replace('%', ''))/100),float(Decimal(row[16].replace(',', '').replace('%', ''))/100),float(Decimal(row[18].replace(',', '').replace('%', ''))/100),float(Decimal(row[20].replace(',', '').replace('%', ''))/100),float(Decimal(row[22].replace(',', '').replace('%', ''))/100),float(Decimal(row[24].replace(',', '').replace('%', ''))/100),float(Decimal(row[26].replace(',', '').replace('%', ''))/100)]
    input_composition_ss[metal_name] = metal_composition_ss    # list
    metal_available_ss= row[9]
    input_stock_ss[metal_name] = float(metal_available_ss.replace(',', ''))   #str


# Problem variables - amount in kg of each input
x_ss = LpVariable.dicts("input_mat", input_mats_ss, 0)

# The objective function is to minimize the total cost of the alloys  for a given quantity in KGS
prob_ss += lpSum([input_costs_ss[i]*x_ss[i] for i in input_mats_ss]), "AlliageCost"

# Quantity constraint in KGS.
prob_ss += lpSum([x_ss[i] for i in input_mats_ss]) == request_quantity_ss, "RequestedQuantity"

# MIN/MAX constraint of Cr in resultant Alloy
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][0] for i in input_mats_ss]) >= Cr_min*request_quantity_ss, "MinCr"
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][0] for i in input_mats_ss]) <= Cr_max*request_quantity_ss, "MaxCr"

# MIN/MAX constraints of cromium in resultant Alloy
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][1] for i in input_mats_ss]) >= Ni_min*request_quantity_ss, "MinNi"
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][1] for i in input_mats_ss]) <= Ni_max*request_quantity_ss, "MaxNi"

# MIN/MAX constraints of Mo in resultant Alloy
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][2] for i in input_mats_ss]) >= Mo_min*request_quantity_ss, "MinMo"
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][2] for i in input_mats_ss]) <= Mo_max*request_quantity_ss, "MaxMo"

# MIN/MAX constraints of Cu in resultant Alloy
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][3] for i in input_mats_ss]) >= Cu_min*request_quantity_ss, "MinCu"
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][3] for i in input_mats_ss]) <= Cu_max*request_quantity_ss, "MaxCu"

# MIN/MAX constraints of Sn in resultant Alloy
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][4] for i in input_mats_ss]) >= Sn_min*request_quantity_ss, "MinSn"
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][4] for i in input_mats_ss]) <= Sn_max*request_quantity_ss, "MaxSn"

# MIN/MAX constraints of Pb in resultant Alloy
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][5] for i in input_mats_ss]) >= Pb_min*request_quantity_ss, "MinPb"
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][5] for i in input_mats_ss]) <= Pb_max*request_quantity_ss, "MaxPb"

# MIN/MAX constraints of Co in resultant Alloy
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][6] for i in input_mats_ss]) >= Co_min*request_quantity_ss, "MinCo"
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][6] for i in input_mats_ss]) <= Co_max*request_quantity_ss, "MaxCo"

# MIN/MAX constraints of S in resultant Alloy
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][7] for i in input_mats_ss]) >= S_min*request_quantity_ss, "MinS"
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][7] for i in input_mats_ss]) <= S_max*request_quantity_ss, "MaxS"

# MIN/MAX constraints of P in resultant Alloy
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][8] for i in input_mats_ss]) >= P_min*request_quantity_ss, "MinP"
prob_ss += lpSum([x_ss[i]*input_composition_ss[i][8] for i in input_mats_ss]) <= P_max*request_quantity_ss, "MaxP"



# MAX constraints of available stock
for i in input_mats_ss:
    prob_ss += x_ss[i] <= input_stock_ss[i], ("MaxStock_" + i)

# Solve the problem
prob_ss.solve()

# The status of the solution
print ("Status:", LpStatus [prob_ss.status])

# Dislay the optimums of each var
for v in prob_ss.variables ():
    print (v.name, "=", v.varValue)

# Display metal compositions
Cr_value = sum([x_ss[i].varValue*input_composition_ss[i][0] for i in input_mats_ss])/request_quantity_ss
Ni_value = sum([x_ss[i].varValue*input_composition_ss[i][1] for i in input_mats_ss])/request_quantity_ss
Mo_value = sum([x_ss[i].varValue*input_composition_ss[i][2] for i in input_mats_ss])/request_quantity_ss
Cu_value = sum([x_ss[i].varValue*input_composition_ss[i][3] for i in input_mats_ss])/request_quantity_ss
Sn_value = sum([x_ss[i].varValue*input_composition_ss[i][4] for i in input_mats_ss])/request_quantity_ss
Pb_value = sum([x_ss[i].varValue*input_composition_ss[i][5] for i in input_mats_ss])/request_quantity_ss
Co_value = sum([x_ss[i].varValue*input_composition_ss[i][6] for i in input_mats_ss])/request_quantity_ss
S_value = sum([x_ss[i].varValue*input_composition_ss[i][7] for i in input_mats_ss])/request_quantity_ss
P_value = sum([x_ss[i].varValue*input_composition_ss[i][8] for i in input_mats_ss])/request_quantity_ss

print ("Cr content: " + str(Cr_value))
print ("Ni content: " + str(Ni_value))
print ("Mo content: " + str(Mo_value))
print ("Cu content: " + str(Cu_value))
print ("Sn content: " + str(Sn_value))
print ("Pb content: " + str(Pb_value))
print ("Co content: " + str(Co_value))
print ("S content: " + str(S_value))
print ("P content: " + str(P_value))

# The result of the objective function is here
print ("Total", value (prob_ss.objective))


