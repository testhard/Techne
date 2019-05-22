nomi=[]
nomericetta=input("INSERIRE NOME RICETTA")
quantita=[]
file=open(nomericetta+ ".txt", "w")
while(1):
  inp=(input("inserire ingrediente o inserire x per uscire"))
  if inp=='x':
    break;
  nomi.append(inp)
  quantita.append(input("inserire quantita"))
somma=0
for i in range(len(quantita)):
  somma+=int(quantita[i])
file.write(str(len(nomi))+";")
for i in range(len(nomi)):
  file.write(nomi[i]+";")
for i in range(len(quantita)):
  file.write(str(int(quantita[i])*(1/somma))+";")
file.close()
'''
memo2012sistemi
'''
