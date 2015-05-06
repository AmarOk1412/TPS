clear;close all; clc;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        option = 4;
        
        % 1: affichage de vos donnees
        % 2: affichage de vos donnees et d'une droite (à vous d'adapter le
        %           coeff a)
        % 3: affichage d'un polynôme d'un degre 2 (idem)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% remarque: les fichiers tailles.m et temps.m (generes par tab_to_matlab)
% doivent être dans le repertoire courant
taillesFFT; % execution du script tailles.m 
tempsFFT;   % execution du script temps.m

x = T_tailles;
y = T_temps;
plot(x,y,'.r'); % affichage des temps de calcul
xlabel('taille (n)','FontSize', 30);
ylabel('temps','FontSize', 30);

p = polyfit(x,y,2)

if (option==1)
    legend('donnees');
elseif (option==2)
    % affichage d'une droite 
    a = 0.00014; % à adapter
    b = 1.7; % theoriquement à adapter mais on peut laisser 0 par approximation
    y_droite = a*x+b;
    hold on;
    plot(x,y_droite,'b'); % affichage du polynôme
    hold off;
    legend('donnees','test de regression manuelle');
elseif (option==3)
    % affichage d'un polynôme de degre 2
    a = 0.000000254; % à adapter
    b=0;   % theoriquement à adapter mais on peut laisser 0 par approximation
    c=0;   % theoriquement à adapter mais on peut laisser 0 par approximation
    y_quadratique = a*x.^2+b*x+c;
    hold on;
    plot(x,y_quadratique,'b'); % affichage du polynôme
    hold off;
    legend('donnees','test de regression manuelle');
elseif (option==4)
    a = 0.000008; % à adapter
    y_nlogn = a*x.*log(x);
    hold on;
    plot(x,y_nlogn,'b'); % affichage du polynôme
    hold off;
    legend('donnees','test de regression manuelle');
end
