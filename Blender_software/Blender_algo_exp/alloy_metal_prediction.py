#!/usr/bin/env python
# coding: utf-8

# In[21]:



# Import the PuLP lib
from pulp import *

# Create the problem variable
prob = LpProblem ("MinimiserLpAlliage", LpMinimize)

# Problem Data
input_mats = ["T_1", "T_2", "T_3",
              "T_4", "T_5",
              "S_1", "S_2", "S_3", "S_4"]

input_costs = {"T_1": 1.20, "T_2": 1.50, "T_3": 0.90,"T_4": 1.75, "T_5":2.6,
               "S_1":   1.30, "S_2": 1.45, "S_3":   1.20, "S_4":   1.00}

#                               Fe%   Cu%   Mn%   Cr%     Ni%   Sn%
input_composition = {"T_1": [0.050, 0.000,  0.013, 0.057, 0.070,  0.013],
                     "T_2": [0.130, 0.000,  0.008, 0.130, 0.040,  0.080],
                     "T_3": [0.900, 0.363,  0.000, 0.020, 0.013,  0.030],
                     "T_4": [0.230, 0.000,  0.008, 0.030, 0.040,  0.018],
                     "T_5": [0.720, 0.384,  0.000, 0.025, 0.033,  0.021],
                     "S_1": [0.650, 0.300,  0.000, 0.017, 0.090,  0.140],
                     "S_2": [0.700, 0.360,  0.040, 0.150, 0.160,  0.040],
                     "S_3": [0.800, 0.704,  0.012, 0.130, 0.004,  0.002],
                     "S_4": [0.990, 0.816,  0.001, 0.190, 0.014,  0.102]}

input_stock = {"T_1": 4000, "T_2": 3000, "T_3": 6000,"T_4": 3000, "T_5": 6000,
               "S_1": 5000, "S_2":  2000,"S_3": 3000, "S_4": 2500}

request_quantity = 150

Iron_min = 0.627
Iron_max = 0.699

Cu_min = 0.360
Cu_max = 0.380

Mn_min = 0.012
Mn_max = 0.0165


Cr_min = 0.012
Cr_max = 0.015

Ni_min = 0.012
Ni_max = 0.015


# Problem variables - amount in kg of each input
x = LpVariable.dicts("input_mat", input_mats, 0)

# The objective function is to minimize the total cost of the alloys  for a given quantity in KGS
prob += lpSum([input_costs[i]*x[i] for i in input_mats]), "AlliageCost"

# Quantity constraint in KGS.
prob += lpSum([x[i] for i in input_mats]) == request_quantity, "RequestedQuantity"

# MIN/MAX constraint of Iron in resultant Alloy
prob += lpSum([x[i]*input_composition[i][0] for i in input_mats]) >= Iron_min*request_quantity, "MinIron"
prob += lpSum([x[i]*input_composition[i][0] for i in input_mats]) <= Iron_max*request_quantity, "MaxIron"

# MIN/MAX constraints of copper in resultant Alloy
prob += lpSum([x[i]*input_composition[i][1] for i in input_mats]) >= Cu_min*request_quantity, "MinCu"
prob += lpSum([x[i]*input_composition[i][1] for i in input_mats]) <= Cu_max*request_quantity, "MaxCu"

# MIN/MAX constraints of manganese in resultant Alloy
prob += lpSum([x[i]*input_composition[i][2] for i in input_mats]) >= Mn_min*request_quantity, "MinMn"
prob += lpSum([x[i]*input_composition[i][2] for i in input_mats]) <= Mn_max*request_quantity, "MaxMn"


# MIN/MAX constraints of cromium in resultant Alloy
prob += lpSum([x[i]*input_composition[i][2] for i in input_mats]) >= Cr_min*request_quantity, "MinCr"
prob += lpSum([x[i]*input_composition[i][2] for i in input_mats]) <= Cr_max*request_quantity, "MaxCr"

# MIN/MAX constraints of cromium in resultant Alloy
prob += lpSum([x[i]*input_composition[i][2] for i in input_mats]) >= Ni_min*request_quantity, "MinNi"
prob += lpSum([x[i]*input_composition[i][2] for i in input_mats]) <= Ni_max*request_quantity, "MaxNi"


# MAX constraints of available stock
for i in input_mats:
    prob += x[i] <= input_stock[i], ("MaxStock_" + i)

# Solve the problem
prob.solve()

# The status of the solution
print ("Status:", LpStatus [prob.status])

# Dislay the optimums of each var
for v in prob.variables ():
    print (v.name, "=", v.varValue)

# Display mat'l compositions
Iron_value = sum([x[i].varValue*input_composition[i][0] for i in input_mats])/request_quantity
Cu_value = sum([x[i].varValue*input_composition[i][1] for i in input_mats])/request_quantity
Mn_value = sum([x[i].varValue*input_composition[i][2] for i in input_mats])/request_quantity
Cr_value = sum([x[i].varValue*input_composition[i][2] for i in input_mats])/request_quantity
Ni_value = sum([x[i].varValue*input_composition[i][2] for i in input_mats])/request_quantity

print ("Iron content: " + str(Iron_value))
print ("Copper content: " + str(Cu_value))
print ("Manganese content: " + str(Mn_value))
print ("Cromium content: " + str(Cr_value))
print ("Nickle content: " + str(Ni_value))
# The result of the objective function is here
print ("Total", value (prob.objective))


# In[21]:





# In[ ]:




