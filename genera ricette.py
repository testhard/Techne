#! /usr/bin/env python
#  -*- coding: utf-8 -*-
#
# GUI module generated by PAGE version 4.23
#  in conjunction with Tcl version 8.6
#    May 23, 2019 10:07:46 AM CEST  platform: Windows NT

import sys
import tkinter as tk
import os
import re

try:
    import ttk
    py3 = False
except ImportError:
    import tkinter.ttk as ttk
    py3 = True




def inserisci():
    global nomi
    global quantita
    global somma
    ing=ingrediente.get()
    quan=g.get()
    if ing and quan:
        try:
            nquan=int(quan)
            somma += nquan
            g.delete(0,'end')
            ingrediente.delete(0,'end')
            nomi.append(ing)
            quantita.append(quan)
            print(nomi)
            print(quantita)
            print(somma)
        except:
            print("non è stato inserito un numero")

            
def genera():
    global nomi
    global quantita
    global somma
    if nome.get():
        if quantita and nomi:
            nomericetta=nome.get()
            nome.delete(0,'end')
            file=open(nomericetta+".txt","w")
            file.write(str(len(nomi))+";")
            for i in range(len(nomi)):
                file.write(nomi[i]+";")
            for i in range(len(quantita)):
                file.write(str(int(quantita[i])*(1/somma))+";")
            file.close()
        nomi=[]
        quantita=[]
        somma=0
    else:
        print("noName")


top = tk.Tk()

'''
This class configures and populates the toplevel window.
top is the toplevel containing window.
'''

_bgcolor = '#d9d9d9'  # X11 color: 'gray85'
_fgcolor = '#000000'  # X11 color: 'black'
_compcolor = '#d9d9d9' # X11 color: 'gray85'
_ana1color = '#d9d9d9' # X11 color: 'gray85'
_ana2color = '#ececec' # Closest X11 color: 'gray92'

top.geometry("413x237+759+225")
top.title("GENERATORE DI RICETTE")
top.configure(background="#424242")
top.configure(highlightbackground="#f0f0f0")
top.configure(highlightcolor="#000000")

ingrediente = tk.Entry(top)
ingrediente.place(relx=0.024, rely=0.422,height=20, relwidth=0.567)
ingrediente.configure(background="white")
ingrediente.configure(disabledforeground="#a3a3a3")
ingrediente.configure(font="TkFixedFont")
ingrediente.configure(foreground="#000000")
ingrediente.configure(insertbackground="black")
ingrediente.configure(width=234)

g = tk.Entry(top)
g.place(relx=0.387, rely=0.549,height=20, relwidth=0.203)
g.configure(background="white")
g.configure(disabledforeground="#a3a3a3")
g.configure(font="TkFixedFont")
g.configure(foreground="#000000")
g.configure(insertbackground="black")
g.configure(width=84)

nome = tk.Entry(top)
nome.place(relx=0.048, rely=0.084,height=20, relwidth=0.397)
nome.configure(background="white")
nome.configure(disabledforeground="#a3a3a3")
nome.configure(font="TkFixedFont")
nome.configure(foreground="#000000")
nome.configure(insertbackground="black")

Label1 = tk.Label(top)
Label1.place(relx=0.46, rely=0.084, height=21, width=90)
Label1.configure(background="#424242")
Label1.configure(disabledforeground="#a3a3a3")
Label1.configure(foreground="#ffffff")
Label1.configure(highlightbackground="#f0f0f0f0f0f0")
Label1.configure(text='''NOME RICETTA''')

Label2 = tk.Label(top)
Label2.place(relx=0.605, rely=0.422, height=21, width=78)
Label2.configure(background="#424242")
Label2.configure(disabledforeground="#a3a3a3")
Label2.configure(foreground="#ffffff")
Label2.configure(text='''INGREDIENTE''')

Label3 = tk.Label(top)
Label3.place(relx=0.605, rely=0.549, height=21, width=13)
Label3.configure(background="#424242")
Label3.configure(disabledforeground="#a3a3a3")
Label3.configure(foreground="#ffffff")
Label3.configure(text='''g''')

Button2 = tk.Button(top, command=genera)
Button2.place(relx=0.048, rely=0.759, height=24, width=377)
Button2.configure(activebackground="#ececec")
Button2.configure(activeforeground="#000000")
Button2.configure(background="#898989")
Button2.configure(disabledforeground="#474747")
Button2.configure(foreground="#000000")
Button2.configure(highlightbackground="#d9d9d9")
Button2.configure(highlightcolor="black")
Button2.configure(pady="0")
Button2.configure(text='''SCRIVI FILE''')
Button2.configure(width=377)

Button2_2 = tk.Button(top, command=inserisci)
Button2_2.place(relx=0.847, rely=0.422, height=54, width=57)
Button2_2.configure(activebackground="#ececec")
Button2_2.configure(activeforeground="#000000")
Button2_2.configure(background="#898989")
Button2_2.configure(disabledforeground="#474747")
Button2_2.configure(foreground="#000000")
Button2_2.configure(highlightbackground="#d9d9d9")
Button2_2.configure(highlightcolor="black")
Button2_2.configure(pady="0")
Button2_2.configure(text='''INSERISCI''')
Button2_2.configure(width=57)

somma=0
nomi=[]
quantita=[]

top.resizable(width=False, height=False)
top.mainloop()

riceptList=[]
fileList=os.listdir()

for i in range(len(fileList)):
    if re.search(r".txt",fileList[i]):                              #utilizzo di regex per individuare i txt
      riceptList.append(fileList[i].replace(".txt", ""))
file=open("main.lt","w")
file.write(str(len(riceptList))+";")
for i in range(len(riceptList)):
    file.write(riceptList[i]+";")
file.close()























































