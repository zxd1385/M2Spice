cmake_minimum_required(VERSION 3.30)
project(M2Spice)

set(CMAKE_CXX_STANDARD 20)

add_executable(M2Spice main.cpp
        View/View.cpp
        View/View.h
        Controller/ProggramController.cpp
        Controller/ProggramController.h
        Controller/AnalisisAlgorithms/LUdecomposition.cpp
        Controller/AnalisisAlgorithms/LUdecomposition.h
        Controller/AnalisisAlgorithms/MNAanalisis.cpp
        Controller/AnalisisAlgorithms/MNAanalisis.h
        Model/Element.cpp
        Model/Element.h
        Model/DerivedElements/Resistor.cpp
        Model/DerivedElements/Resistor.h
        Model/DerivedElements/Capacitor.cpp
        Model/DerivedElements/Capacitor.h
        Model/DerivedElements/Inductor.cpp
        Model/DerivedElements/Inductor.h
        CurrentSource.cpp
        CurrentSource.h
        Model/DerivedElements/VoltageSource.cpp
        Model/DerivedElements/VoltageSource.h
        Model/Circuit.cpp
        Model/Circuit.h
        Model/Graph.cpp
        Model/Graph.h)
