%% Pr�ctica Identificaci�n de Sistemas
clc
clear all
close all
Datos=load('muestras15nov.csv'); %Cargar los datos del excel y guardarlos en la variable
OUT=Datos(:,1); %Salida del Sistema
IN=Datos(:,2); %Entrada del Sistema
Time=(0:1:length(Datos)-1)'; %Vector de tiempo
%% Gr�fica de los datos
figure(1)
plot(Time,IN); %Se grafica la entrada del sistema
title('Entrada: Activacion de motor')
ylabel('Motor')
xlabel('Tiempo [s]')
grid on

%% Gr�fica
figure
plot(OUT);

%% Gr�fica
figure
salida=smooth(OUT);

%% Gr�fica
figure(2)
plot(Time,salida); %Se grafica la salida del sistema
title('Salida: Temperatura')
ylabel('Temperatura [C]')
xlabel('Tiempo [s]')
grid on

%% Identificaci�n de sistemas
%%systemIdentification %Se llama un comando de matlab importante para la identificaci�n

%% Funci�n de Transferencia obtenida (Metodo 3)
%%G=tf(d2c(bj33431));%<---Modelo con mejor FIT
G=tf(d2c(bj44444));
num=cell2mat(G.numerator);
den=cell2mat(G.denominator);
FTmotor=tf(num,den)

%%
Time=(0:1:length(IN)-1)'; %Vector de tiempo
y = lsim(G,IN,Time); % system response
figure(1)
plot(y);
hold on;
plot(IN);
plot(salida);
legend('Estimate','Input','Output');
