clear;close all; clc;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        option = 1;
        
        % 1: affichage de vos données
        % 2: affichage de vos données et d'une droite (à vous d'adapter le
        %           coeff a)
        % 3: affichage d'un polynôme d'un degré 2 (idem)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% remarque: les fichiers tailles.m et temps.m (générés par tab_to_matlab)
% doivent être dans le répertoire courant
tailles; % execution du script tailles.m 
temps;   % execution du script temps.m

x = T_tailles;
y = T_temps;
plot(x,y,'.r'); % affichage des temps de calcul
xlabel('taille (n)','FontSize', 30);
ylabel('temps','FontSize', 30);

if (option==1)
    legend('données');
elseif (option==2)
    % affichage d'une droite 
    a = 0.001; % à adapter
    b = 0; % théoriquement à adapter mais on peut laisser 0 par approximation
    y_droite = a*x+b;
    hold on;
    plot(x,y_droite,'b'); % affichage du polynôme
    hold off;
    legend('données','test de regression manuelle');
elseif (option==3)
    % affichage d'un polynôme de degré 2
    a = 0.001; % à adapter
    b=0;   % théoriquement à adapter mais on peut laisser 0 par approximation
    c=0;   % théoriquement à adapter mais on peut laisser 0 par approximation
    y_quadratique = a*x.^2+b*x+c;
    hold on;
    plot(x,y_quadratique,'b'); % affichage du polynôme
    hold off;
    legend('données','test de regression manuelle');
end