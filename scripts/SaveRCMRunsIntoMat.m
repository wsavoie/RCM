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
    
    [lw,phi,ang1,ang2,L,W,D,vp]=deal(zeros(length(innerFolds),1));
    for j=1:length(innerFolds)
        innerName=[fold,'\',outerFolds(i).name,'\',innerFolds(j).name,'\'];
        [lw(j), phi(j), ang1(j), ang2(j),L(j),W(j),D(j),vp(j)]=rcm(horzcat(innerName),C);
    end
    temp = [lw ang1 ang2 phi];
    temp = sortrows(temp,[2,3]);
    phiSurf=[temp];
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
    LW=lw(1);
    LWs(i)=LW;
%     phis(i)=phi;
save([fold,'/',outerFolds(i).name,'/','phiLW.mat'],'phiSurf','LW','L','W','vp','D');
end
% save('phiErr.mat')


%% create the 3d data version
phiVol=[]; LVol=[]; WVol=[]; DVol=[]; vpVol=[];
for i=1:length(outerFolds)
    load(fullfile(fold,outerFolds(i).name,'phiLW.mat'));
    lwI(i)=LW;
    lw=phiSurf(:,1); ang1=phiSurf(:,2); ang2=phiSurf(:,3); phi=phiSurf(:,4);
    A1=unique(ang1);
    A2=unique(ang2);
    
    [A1q,A2q]=meshgrid(A1,A2);
    
    Ls=reshape(L,[length(A1),length(A2)]);
    Ws=reshape(W,[length(A1),length(A2)]);
    Ds=reshape(D,[length(A1),length(A2)]);
    vps=reshape(vp,[length(A1),length(A2)]);
    phis = reshape(phi,[length(A1),length(A2)]);
    phiVol(:,:,i)=phis;
    LVol(:,:,i)=Ls;
    WVol(:,:,i)=Ws;
    DVol(:,:,i)=Ds;
    vpVol(:,:,i)=vps;
end
[lwI,ord]=sort(lwI);
phiVol=phiVol(:,:,ord);
LVol=LVol(:,:,ord);
WVol=WVol(:,:,ord);
DVol=DVol(:,:,ord);
vpVol=vpVol(:,:,ord);
save([fold,'/','phiVol.mat'],'phiVol','lwI','A1','A2','LVol','WVol','DVol','vpVol');



figText(gcf,14);
figure(45);
hold on;
% plot(LWs,phis,'o-');
axis([0 1.4 0.05 0.3]);
