#! /usr/local/bin/python3

import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

from scipy.constants import epsilon_0
import cmasher as cmr

import mplhep as hep
mpl.style.use([hep.style.ATLAS, 'dark_background'])

import time

def jacobi(U, C, delta):
    '''Return jacobi method relaxation

    Parameters
    ----------
    U: `np.ndarray`
    potential scalar-field 
    C: `np.ndarray`
    density scalar-field

    Returns
    -------
    U: `np.ndarray`
    relaxed scalar field
    '''
    
    U[1:-1, 1:-1] = (
        1 / 4 
        *
        (
            U[2:, 1:-1]
            + 
            U[0:-2, 1:-1]
            +
            U[1:-1, 2:]
            +
            U[1:-1, 0:-2]
        )
        +
        1 / 4
        *
        C[1:-1, 1:-1]
        *
        delta**2
    )

    return U

def gaus(U, C, delta):
    '''Return Gauss-Seidel method relaxation

    Parameters
    ----------
    U: `np.ndarray`
    potential scalar-field 
    C: `np.ndarray`
    density scalar-field

    Returns
    -------
    U: `np.ndarray`
    relaxed scalar field
    '''

    I, J = np.shape(U)

    for i in range(1, I-2):
        for j in range(1, J-2):
            U[i, j] = (
                1 / 4
                *
                (
                    U[i+1, j]
                    +
                    U[i-1, j]
                    +
                    U[i, j+1]
                    +
                    U[i, j-1]
                )
                +
                1 / 4
                *
                C[i, j]
                *
                delta**2
            )
    
    return U

def sor(U, C, delta, omega):
    '''Return Successive Over-Relaxation method

    Parameters
    ----------
    U: `np.ndarray`
    potential scalar-field 
    C: `np.ndarray`
    density scalar-field

    Returns
    -------
    U: `np.ndarray`
    relaxed scalar field
    '''

    I, J = np.shape(U)

    r = np.zeros_like(U)
    
    U_old = np.zeros_like(U)
    U_old[:,:] = U[:,:]

    for i in range(1, I-2):
        for j in range(1, J-2):
            r[i, j] = (
                1 / 4
                *
                (
                    U[i+1, j]
                    +
                    U[i-1, j]
                    +
                    U[i, j+1]
                    +
                    U[i, j-1]
                )
                +
                1 / 4
                *
                C[i, j]
                *
                delta**2
                - 
                U_old[i, j]
            )

            U[i,j] = U_old[i,j] + omega * r[i,j]
    
    return U


def convergence(U_n0: np.ndarray, U_n1: np.ndarray, epsilon_a: float, epsilon_r: float, iteration):
    delta_ij = np.abs(U_n1 - U_n0)
    test = delta_ij < epsilon_a * np.ones_like(U_n0) + np.abs(U_n1) * epsilon_r
    
    if test.all() == True:
        print('\nconverged in %d iterations'%(iteration))
        return True

    return False


def main(algorithm: str = 'jacobi'):
    '''Capacitor Laplace problem solver

    Parameters
    ----------
    algorithm: `str` or `None`
        Relaxation solver algorithm possibilities are
         - `jacobi` to use Jacobi method
         - `gaus` to use Gauss-Seidel method
         - `sor` to use Successive Over-Relaxation
    '''
    
    PLOT_EVERY = 10000000 ## NEVER PLOT (ONLY AT END)
    SAMPLE_SIZE = 100
    SAMPLE_HALF_LENGHT = 0.5
    PLATE_HALF_WIDTH = 0.25
    PLATE_POSITION = 0.2
    PLATE_CHARGE = 1.0

    potential_matrix = np.zeros((
        SAMPLE_SIZE,
        SAMPLE_SIZE
    ))

    potential_matrix_previous_iter = np.zeros_like(potential_matrix)

    coordinates_x = np.linspace(-SAMPLE_HALF_LENGHT, SAMPLE_HALF_LENGHT, SAMPLE_SIZE)
    coordinates_y = np.linspace(-SAMPLE_HALF_LENGHT, SAMPLE_HALF_LENGHT, SAMPLE_SIZE)
    delta = coordinates_x[1] - coordinates_x[0]

    coordinates_x_mesh, coordinates_y_mesh = np.meshgrid(
        coordinates_x,
        coordinates_y
    )

    charge_density = np.zeros_like(potential_matrix)
    
    plate_index_positive = int(
        (
            SAMPLE_SIZE - 1
        )
        * 
        (
            SAMPLE_HALF_LENGHT + PLATE_POSITION
        )
        /
        (
            2 * SAMPLE_HALF_LENGHT
        )
    ) + 1

    plate_index_negative = int(
        (
            SAMPLE_SIZE - 1
        )
        *
        (
            SAMPLE_HALF_LENGHT - PLATE_POSITION
        )
        /
        (
            2 * SAMPLE_HALF_LENGHT
        )
    ) + 1

    plate_widht_index_upper = int(
        (
            SAMPLE_SIZE - 1
        )
        *
        (
            SAMPLE_HALF_LENGHT + PLATE_HALF_WIDTH
        )
        /
        (
            2 * SAMPLE_HALF_LENGHT
        )
    ) + 1

    plate_widht_index_lower = int(
        (
            SAMPLE_SIZE - 1
        )
        *
        (
            SAMPLE_HALF_LENGHT - PLATE_HALF_WIDTH
        )
        /
        (
            2 * SAMPLE_HALF_LENGHT
        )
    ) + 1

    charge_density[plate_widht_index_lower:plate_widht_index_upper, plate_index_positive] = + 1.5 * PLATE_CHARGE
    charge_density[plate_widht_index_lower:plate_widht_index_upper, int((SAMPLE_SIZE - 1)/ 2) + 1] = - 2 * PLATE_CHARGE
    charge_density[plate_widht_index_lower:plate_widht_index_upper, plate_index_negative] = + 1.5 * PLATE_CHARGE

    plate_position = np.copy(np.abs(charge_density))


    plt.figure()

    iteration = 0

    sim_time = time.time()

    while True:

        if algorithm == 'sor':
            potential_matrix_previous_iter[:,:] = potential_matrix[:,:]
            potential_matrix = sor(
                potential_matrix,
                charge_density / epsilon_0,
                delta,
                1.8
            )
        else: 
            potential_matrix_previous_iter[:,:] = potential_matrix[:,:]

            if algorithm == 'jacobi':
                potential_matrix = jacobi(potential_matrix, charge_density / epsilon_0, delta)
        
            elif algorithm == 'gaus':
                potential_matrix = gaus(potential_matrix, charge_density / epsilon_0, delta)
        
            else:
                raise NotImplementedError('%s: algorithm still not implemented'%algorithm) 


        electric_field_y, electric_field_x = np.gradient(potential_matrix)
        electric_field_x, electric_field_y = - electric_field_x / epsilon_0, - electric_field_y / epsilon_0
        
        print('\riteration: %d'%iteration, end='')
        iteration += 1

        if convergence(potential_matrix_previous_iter, potential_matrix, 0.001, 0.001, iteration):
            break
    
    print('computation time: %s s'%(time.time() - sim_time))

    plt.clf()

    plt.contourf(
        coordinates_x_mesh,
        coordinates_y_mesh,
        potential_matrix,
        cmap = cmr.emergency_s,
        norm = mpl.colors.CenteredNorm(0),
        levels = 15
    )
    plt.colorbar()

    plt.streamplot(
        coordinates_x,
        coordinates_y,
        electric_field_x,
        electric_field_y,
        linewidth = 1,
        color = 'w',
        density = 1.5
    )

    plt.savefig('plot.pdf', bbox_inches = 'tight')
    plt.show()

if __name__ == '__main__':
    # algorithm = input('algorithm ["jacobi", "gaus" or "sor"]: ')
    main('sor')
