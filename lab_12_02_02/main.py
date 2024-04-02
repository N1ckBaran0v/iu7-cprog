import myarr
from tkinter import *
from tkinter import messagebox as box

def main():
    window = Tk()
    window.geometry("450x400")
    window.resizable(width=False, height=False)
    window.configure(bg="#000000")
    window.title("Lab 12 Task 2")

    def to_fib(self):
        nonlocal is_fib, func
        label_do.configure(text = "Input number:")
        label_fib.configure(bg = "#FF0000", fg = "#000000")
        label_places.configure(bg = "#000000", fg = "#FF0000")  
        is_fib = True   
        func = myarr.fill_by_fib   

    def to_places(self):
        nonlocal is_fib, func
        label_do.configure(text = "Input numbers:")
        label_fib.configure(bg = "#000000", fg = "#FF0000")
        label_places.configure(bg = "#FF0000", fg = "#000000")  
        is_fib = False 
        func = myarr.pos_first_found
    
    def just_do_it():
        title = "Answer"
        txt = "random_text.exe"
        arg = None
        if is_fib:
            try:
                arg = int(my_entry.get())
            except Exception:
                arg = None
                title = "Error"
                txt = "Invalid data"
        else:
            try:
                arg = list(map(int, my_entry.get().split()))
            except Exception:
                arg = None
                title = "Error"
                txt = "Invalid data"
        if arg is not None:
            txt = str(" ".join(map(str, func(arg))))
        box.showinfo(title, txt)

    label_ask = Label(window, bg='#000000', font='Ubuntu 24', fg='#FF0000', text='Select action', width=20)
    label_ask.place(x=30, y=50)
    label_fib = Label(window, bg='#FF0000', font='Ubuntu 24', fg='#000000', text='Fill array bi Fibonacci', width=20)
    label_fib.place(x=30, y=100)
    label_fib.bind("<Button-1>", to_fib)
    label_places = Label(window, bg='#000000', font='Ubuntu 24', fg='#FF0000', text='Find first position', width=20)
    label_places.place(x=30, y=150)
    label_places.bind("<Button-1>", to_places)
    is_fib = True
    func = myarr.fill_by_fib

    label_do = Label(window, bg='#000000', font='Ubuntu 24', fg='#FF0000', text='Input number:', width=20)
    label_do.place(x=30, y=200)
    my_entry = Entry(window, bg = "#FF0000", font='Ubuntu 24', fg = "#000000", width = 21)
    my_entry.place(x=30, y=250)
    my_btn = Button(window, bg = "#000000", font='Ubuntu 24', fg = "#FF0000", text='Get array', width=20, command=just_do_it)
    my_btn.place(x=30, y=300)

    window.mainloop()


if __name__ == "__main__":
    main()