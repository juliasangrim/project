import pandas as pd

n = 10
print("Test ", n , "x" , n)

df=pd.read_csv('domino_info.csv', sep=';',header=None)

count = 0
sum = 0
for i in range(len(df[0])) :
    if (df[1][i] == 20) :
        print(i)
        count += 1
        sum += df[0][i]

avr = sum / count
# df[0].mean()
print("Avarage: ", avr)
maxim = max(df[1])
print("Maximum domino: ", maxim)

# for  data in df.items() :
#     count = 0
#     if data[1] == 4 :
#         count += 1;
print(count / 1000 * 100)

# print ("Minimum domino: ", min(df[0]))
# print(max(df[0]))

# data = pd.read_csv('all_field_info.csv', sep=';')

# df2 = pd.DataFrame([[n, avr, maxim]], columns= ['n ', 't_avg', 'd_max'])

# data.append(df2)
# data.to_csv('all_field_info.csv', sep=';')
