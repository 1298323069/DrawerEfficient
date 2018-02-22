#!/usr/bin/env python3

import math
# print(math.e)

#***********************************

# number = int(input("Enter an integer: "))
# if number <= 100:
# 	print("Your number is smaller than equal to 100")
# else:
# 	print("Your number is greater than 100")

#***********************************

# amount = float(input("Enter amount: "))  # 输入数额
# inrate = float(input("Enter Interest rate: ")) #输入利率
# period = int(input("Enter period: ")) #输入期限
# value = 0
# year = 1

# while year <= period:
# 	value = amount + (inrate * amount)
# 	print("Year {} Rs. {:.2f}".format(year, value))  # {:.2f}的意思是替换为2位精度的浮点数
# 	amount = value;
# 	year = year + 1


#***********************************
# fahrenheit = 0
# print("Fahrenheit Celsius")
# while fahrenheit <= 250:
# 	Celsius = (fahrenheit - 32) / 1.8      # 转换为摄氏度
# 	print("{:5d}      {:7.2f}".format(fahrenheit, Celsius))  #{:5d}表示为5位的整数不足以空格对齐
# 	fahrenheit = fahrenheit + 25;

#***********************************
# days = int(input("Enter days: "))
# months = days // 30            #只取商的部分
# days = days % 30
# print("Months = {} Days = {}".format(months, days))



#******************类型转换

# a = 8.126768
# print("{}".format(str(a)))   #float(string) int(string) str(integer) str(float)

#*********************
# sum = 0
# for i in range(1, 11):
# 	sum += 1.0 / i
# 	print("{:2d} {:6.4f}".format(i, sum))

#*********************

# a = int(input("Enter value of a: "))
# b = int(input("Enter value of b: "))
# c = int(input("Enter value of c: "))
# d = b * b - 4 * a * c
# if d < 0:
# 	print("ROOTS are imaginary")
# else:
# 	root1 = (-b + math.sqrt(d)) / (2 * a)
# 	root2 = (-b - math.sqrt(d)) / (2 * a)
# 	print("Root 1 = ", root1)
# 	print("Root 2 = ", root2)

#*******************************
# baseSalary = 1500
# bonus_rate = 200
# commision_rate  = 0.02
# cameraNum = int(input("Enter camera num:"))
# cameraPrice = float(input("Enter camera price:"))
# bonus = (bonus_rate *cameraNum)
# commision = (commision_rate * cameraNum * cameraPrice)
# print("Bonus = {:6.2f}".format(bonus))
# print("commision = {:6.2f}".format(commision))
# print("final_salary = {:6.2f}".format(baseSalary + bonus + commision))

radius = float(input("Enter radius of a circle:"))
area = radius * radius * 2 * math.pi
print("radiu = {:6.2f}".format(radius))
print("area = {:6.10f}".format(area))


