import matplotlib.pyplot as plt
import scipy.constants as sc


# CONSTANT
G = sc.G
K = 1 / (4 * sc.pi * sc.epsilon_0)


def aceleration(function):
    def wrapper(self, force, time):
        return function(self, (1 / self.mass) * force, time)
    return wrapper


def multipleObjects(functionForce):
    """Este decorador permite que se pueda calcular la fuerza debido a la
       interaccion con mas de un objeto fisico"""

    def wrapper(self, *objects):
        force = Vector(0, 0, 0)
        for obj in objects:
            force += functionForce(self, obj)
        return force

    return wrapper


class Vector(object):
    """docstring for Vector"""

    def __init__(self, x1, x2, x3):
        self.x1 = x1
        self.x2 = x2
        self.x3 = x3

    def __str__(self):
        """Para imprimir por pantalla el vector"""
        string = '({:.5f}, {:.5f}, {:.5f})'.format(self.x1, self.x2, self.x3)
        return string

    def __add__(self, vector):
        """suma de vectores, operador +"""
        return Vector(self.x1 + vector.x1, self.x2 + vector.x2,
                      self.x3 + vector.x3)

    def __sub__(self, vector):
        """resta de vectores, operador -"""
        return Vector(self.x1 - vector.x1, self.x2 - vector.x2,
                      self.x3 - vector.x3)

    def __rmul__(self, n):
        """multiplicacion de vector por un escalar"""
        return Vector(n * self.x1, n * self.x2, n * self.x3)

    def __mul__(self, vector):
        """producto cruz, operador *"""
        x1 = self.x2 * vector.x3 - self.x3 * vector.x2
        x2 = self.x1 * vector.x3 - self.x3 * vector.x1
        x3 = self.x1 * vector.x2 - self.x2 * vector.x1
        return Vector(x1, -x2, x3)

    def norm(self):
        """norma del vector"""
        return (self.x1 ** 2 + self.x2 ** 2 + self.x3 ** 2) ** 0.5

    def direction(self):
        """vector director del vector"""
        return (1 / self.norm()) * self


class Particle(object):
    """docstring for Particle"""

    def __init__(self, mass, charge, position, velocity):
        self.position = position
        self.velocity = velocity
        self.mass = mass
        self.charge = charge

    def __str__(self):
        """Para imprimir por pantalla informacion de la particula"""
        string = 'Mass: {:.2f}\n'.format(self.mass)
        string += 'Charge: {:.2f}\n'.format(self.charge)
        string += 'Position: ' + str(self.position) + '\n'
        string += 'Velocity: ' + str(self.velocity) + '\n'

        return string

    @multipleObjects
    def gravitationalForce(self, particle):
        """Calcula la fuerza gravitacional debida a la interaccion con otras
           particulas, se pueden pasar a la funcion tantas particulas de
           argumento como se quiera"""
        r = particle.position - self.position
        return (G * self.mass * particle.mass / r.norm() ** 2) * r.direction()

    @multipleObjects
    def electricForce(self, particle):
        """Calcula la fuerza electrica debida a la interaccion con otras
           particulas"""
        r = self.position - particle.position
        return (K * self.charge * particle.charge / r.norm() ** 2) *\
            r.direction()

    @multipleObjects
    def magneticForce(self, magneticField):
        """Calcula la fuerza debida a la interaccion con campos magneticos"""
        return self.charge * (self.velocity * magneticField)

    @aceleration
    def posEvol(self, aceleration, dt):
        return self.position + dt * \
            self.velocity + (0.5 * dt ** 2) * aceleration

    @aceleration
    def velEvol(self, aceleration, dt):
        return self.velocity + dt * aceleration

    def timeEvol(self, force, dt):
        self.position = self.posEvol(force, dt)
        self.velocity = self.velEvol(force, dt)


def tarea(charge=20, maxIteration=10000, dt=0.01):
    p1 = Particle(10, charge, Vector(0, 0, 0), Vector(0, 0, 0))
    p2 = Particle(10, -charge, Vector(1, 0, 0), Vector(0, 0, 0))

    magneticField = Vector(0, 0, 10)

    x1 = []
    y1 = []
    x2 = []
    y2 = []

    for i in range(maxIteration):
        x1.append(p1.position.x1)
        y1.append(p1.position.x2)

        x2.append(p2.position.x1)
        y2.append(p2.position.x2)

        f1 = p1.electricForce(p2) + p1.gravitationalForce(p2) + \
            p1.magneticForce(magneticField)

        f2 = p2.electricForce(p1) + p2.gravitationalForce(p1) + \
            p2.magneticForce(magneticField)

        p1.timeEvol(f1, dt)
        p2.timeEvol(f2, dt)

    plt.plot(x1, y1, '--r', label='Particula 1')
    plt.plot(x2, y2, '--g', label='Particula 2')
    plt.title('Posicion de 2 particulas cargadas sometidas a un campo magnetico')
    plt.xlabel('Posicion en x')
    plt.ylabel('Posicion en y')
    plt.grid()
    plt.legend(loc=0)
    plt.show()


if __name__ == '__main__':
    tarea()
