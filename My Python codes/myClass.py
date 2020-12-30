x="Welcome"
name_input, age_input=raw_input("Hey there, can you write your name and age please using a space ? :").split()
#y=raw_input("Hey there, can you write your name please :")
print
print 'Hi',name_input,',',x
print

class class1:
    def __init__(self, boss_age):
        self.name=name_input
        self.age=int(age_input)
        self.boss_age=boss_age

    def Occupation(self):
        self.job='reaserch'

    def call(self):
        print 'Ok let me guess \n Your name is',self.name, '\n and you are a researcher \n and your age is',self.age
        print
        if(self.name=='Debabrata'):
            print 'So you are my boss \n Hello boss!!!'
            if(self.age!=self.boss_age):
                #print self.age, '\n', self.boss_age
                #print type(self.age), '\n', type(self.boss_age)
                print 'Boss, are you sure you are',self.age,'years old? \n I think you are',self.boss_age
        else :
            print 'And you are not my boss \n what are you doing in his laptop?'
        print
        
#print("File one __name__ is set to: {}" .format(__name__)) // If a module is imported to another module then that module is no longer __main__, only the module being executed is of __name__ main   
if __name__ == "__main__":
    app = class1(27)
    app.call()
    #app.Occupation()
