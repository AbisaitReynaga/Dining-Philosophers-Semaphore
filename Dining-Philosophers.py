from multiprocessing import Process,Semaphore
from time import sleep
from random import randint
from colorama import Fore

#Philosopher class 
class Philosopher(Process):
    def __init__(self,left_fork,right_fork,philos_eating,time_thinking,time_eating):
        super().__init__()
        self._left_fork = left_fork
        self._right_fork = right_fork
        self._philos_eating = philos_eating
        self._time_think = time_thinking
        self._time_eating = time_eating

    #This method is for eat
    def philosopher_eat(self):
        with self._philos_eating: #This handler check the quantity of philosopher eating
            with self._left_fork: #This handler take the left fork
                with self._right_fork: #This handler take the right fork
                    print(Fore.CYAN + self.name + Fore.GREEN +' eating...') #If a philosopher can take both forks, He will eat.
                    sleep(self._time_eating)
                    
    def philosopher_think(self):
        print(Fore.MAGENTA + self.name + Fore.YELLOW +' thinking...')
        
    def run(self):
        while True:
            self.philosopher_eat()
            self.philosopher_think()
            
if __name__ == '__main__':
    forks = [Semaphore(1) for _ in range(5)] #This variable, storage a list of semphore objetcs.
    philos_eating = Semaphore(4) # This variable, storage a semaphore to limit the philosophers eating
    
    filosofo1 = Philosopher(forks[0],forks[1],philos_eating,randint(2,5),randint(1,6))
    filosofo2 = Philosopher(forks[1],forks[2],philos_eating,randint(1,6),randint(2,5))
    filosofo3 = Philosopher(forks[2],forks[3],philos_eating,randint(2,5),randint(1,6))
    filosofo4 = Philosopher(forks[3],forks[4],philos_eating,randint(1,6),randint(2,5))
    filosofo5 = Philosopher(forks[4],forks[0],philos_eating,randint(2,5),randint(1,6))
    

    filosofo1.start()
    filosofo2.start()
    filosofo3.start()
    filosofo4.start()
    filosofo5.start()
    