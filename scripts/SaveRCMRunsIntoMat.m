% directory_name = 'D:\RCMcode\RCM\Results\ushape2\10m 80\';
fold =uigetdir('D:\RCMcode\RCM\Results\');

C=10;
PON = [1 1];
outerFolds = dir2(fold);
outerFolds=outerFolds(find([outerFolds(:).isdir]));

% outerFolds = outerFolds(3:end);
phiSurf=[];
phiErr=[];
figure(5);
hold on;
phiSurf=[];


for(i=1:length(outerFolds)) 
    innerFolds=dir2([fold,'/',outerFolds(i).name]);
    innerFolds=innerFolds(find([innerFolds(:).isdir]));

    for j=1:length(innerFolds)
        innerName=[fold,'\',outerFolds(i).name,'\',innerFolds(j).name,'\'];
        [lw(j), phi(j), ang1(j), ang2(j)]=rcm(horzcat(innerName),C);
    end

    temp = [lw' ang1' ang2' phi'];
    temp = sortrows(temp,[2,3]);
    phiSurf=[phiSurf;temp];
    if PON(2)==2
        
        xlabel('Angle (\circ)');
        ylabel('\phi');
        title('RCM Results for Symmetric Angle Shape 2.5M iterations');
        if lw(3)==0.1;
            OutM=errBarCalc(ang1,phi);
            errorbar(OutM(:,1),OutM(:,2),OutM(:,3),'-o')
            axis([0,120,0.05,0.3]);
            text(OutM(3,1),OutM(end-2,2),horzcat('\itl/w=',num2str(lw(1))))
        end
    end
%     x= errBarCalc(ang1,phi);
%     phiErr = [; lw(1)*ones(size(x,1),1), x(:,1), x(:,2)];
save([fold,'/',outerFolds(i).name,'/','phiLW.mat'],'phiSurf');
end
% save('phiErr.mat')

figText(gcf,14);
figure(45);
hold on;
plot(lw,phi,'o-');
axis([0 1.4 0.05 0.3]);
