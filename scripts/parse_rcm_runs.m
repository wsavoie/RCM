% directory_name = 'AngleChangeLW=0.0';
% directory_name = 'D:\RCMcode\RCM\Results\All angles 1M iterations\AngleChange\';
% directory_name = 'D:\RCMcode\RCM\Results\All angles 1M iterations\AngleChangeLW=0.7\';
directory_name = [pwd,'\..\Results\test'];
folds = dir(directory_name);
folds = folds(3:end);

%decide which things to plot
PON = [1 2];
C=10.8;
for(i=1:length(folds))
[lw(i), phi(i), ang1(i), ang2(i) L(i) W(i) D(i),vp(i)]=rcm(horzcat(directory_name,folds(i).name),C);
end
temp = [lw' ang1' phi'];
temp = sortrows(temp,2);
% phiSurf=[phiSurf;temp];

if PON(1)==1;
    %% plot phi vs. l/w 
    if PON(2)==1;
        hold on;
        xlabel('\it/w');
        ylabel('\rm\phi');
        title('RCM Results for U-Shape 1M iterations');
        OutM=errBarCalc(lw,phi);
        errorbar(OutM(:,1),OutM(:,2),OutM(:,3),'-o')
        hold on;
        axis([0,1.4,0.05,0.3]);
        text(OutM(3,1),OutM(3,2)*1.05,horzcat(num2str(ang1(1)),'\circ'));
        figText(gcf,14);
    end
    %% plot phi vs. single angle
    if PON(2)==2
        hold on;
        xlabel('Angle (\circ)');
        ylabel('\phi');
        title('RCM Results for Symmetric Angle Shape 1M iterations');
        OutM=errBarCalc(ang1,phi);
        errorbar(OutM(:,1),OutM(:,2),OutM(:,3),'-o')
        hold on;
        axis([0,120,0.05,0.3]);
        text(OutM(3,1),OutM(end-2,2),horzcat('\itl/w=',num2str(lw(1))))
        figText(gcf,14);
    end
end