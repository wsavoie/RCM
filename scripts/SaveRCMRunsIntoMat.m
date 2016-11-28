directory_name = 'D:\RCMcode\RCM\Results\ushape2\';
multAngles=0;
C=10.8;
PON = [1 2];
outerFolds = dir(directory_name);
outerFolds = outerFolds(3:end);
phiSurf=[];
phiErr=[];
figure(5);
hold on;



for(i=1:length(outerFolds))
    if(multAngles)
        innerDir = outerFolds(i).name;
        innerName= horzcat(directory_name,'\',innerDir,'\');
        innerFolds = dir(innerName);
        innerFolds = innerFolds(3:end);
    else
        innerFolds=outerFolds;
        innerName= horzcat(directory_name);
    end
    for(j=1:length(innerFolds))
        [lw(j), phi(j), ang1(j), ang2(j)]=rcm(horzcat(innerName,innerFolds(j).name,'\'),C);
    end
    temp = [lw' ang1' phi'];
    temp = sortrows(temp,2);
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
    x= errBarCalc(ang1,phi);
    phiErr = [; lw(1)*ones(size(x,1),1), x(:,1), x(:,2)];
end

figText(gcf,14);

