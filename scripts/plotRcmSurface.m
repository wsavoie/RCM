load('phiErr.mat')
%dont forget phi error
figure(2)
lws = unique(phiErr(:,1));
angs = unique(phiErr(:,2));



phis = reshape(phiErr(:,3),[length(angs),length(lws)]);
surf(lws,angs,phis);

title('\phi(\alpha,\itl/w)');
xlabel('\itl/w');
ylabel('\alpha(\circ)');
zlabel('\phi');
figText(gcf,14);


%% plot phi vs. single angle
figure(3)
hold on;
xlabel('Angle (\circ)');
ylabel('\phi');
title('RCM Results for Symmetric Angle');

% hold on;
for(i=1:length(lws))
idx=(i-1)*13+1;

OutM=errBarCalc(angs,phis(idx:idx+12));
errorbar(OutM(:,1),OutM(:,2),OutM(:,3),'-o')
text(OutM(end,1),OutM(end,2),horzcat('\itl/w=',num2str(lws(i))));
end
axis([0,120,0.05,0.3]);
figText(gcf,14);

%%
figure(3)

[idx,val]=find(phiErr(:,2)==0.0);
LD=phiErr(idx,1);
phild = phiErr(idx,3);
phild = phild*10.5/10;
LD=14+2*14*LD
plot(LD,phild);
axis([0,140,0,.7]);

% lwTest = .9;
% angTest = 60;
% [row,~,~] = find(phiSurf(:,1)==lwTest);
% [row,~,~] = find(phiSurf(row,2)==angTest);
% val = phiSurf(row,3)
% % 
% % [~, idx] = min(abs( - 4.756));
% % pH_Mid_Pt2 = pH(idx);
% % Vb_Mid_Pt2 = Vb(idx);
% [~,idx]=min(abs(.1317-phiSurf(:,3)))
% 
% phiSurf(idx,3)

%% plot a1 vs. a2 contour and surface for single LW
fold = uigetdir('D:\RCMcode\RCM\Results\');
load([fold,'/phiLW.mat']);
% temp = [lw' ang1' ang2' phi'];
maxA1=max(phiSurf(:,2)); minA1=min(phiSurf(:,2));
maxA2=max(phiSurf(:,3)); minA2=min(phiSurf(:,3));
lw=phiSurf(:,1); ang1=phiSurf(:,2); ang2=phiSurf(:,3); phi=phiSurf(:,4);
A1=unique(ang1);
A2=unique(ang2);
phis = reshape(phi,[length(A1),length(A2)]);
% [X,Y]=meshgrid(ang1,ang2);
figure(1)
surf(A1,A2,phis);
xlabel('\alpha_1');ylabel('\alpha_2');zlabel('\phi');
axis([-130 130 -130 130 0.085, 0.13]);
figure(2)
contour(A1,A2,phis);
xlabel('\alpha_1');ylabel('\alpha_2');


%% plot a1 vs. a2 contour and surface for all one after the other 

fold = uigetdir('D:\RCMcode\RCM\Results\');
load([fold,'/phiVol.mat']);
% temp = [lw' ang1' ang2' phi'];
figure(1)
for i=size(phiVol,3):-1:1

subplot(1,2,1)
phis=squeeze(phiVol(:,:,i));
surf(A1,A2,phis);
xlabel('\alpha_1');ylabel('\alpha_2');zlabel('\phi');
axis([-120,120,-120,120,.05,.3])
suptitle(['L/W=',num2str(lwI(i))]);
subplot(1,2,2);
contour(A1,A2,phis);
xlabel('\alpha_1');ylabel('\alpha_2');

pause;
end

%% plot staple shape from phiVol matrix
fold = uigetdir('D:\RCMcode\RCM\Results\');
load([fold,'/phiVol.mat']);
figure(5);
s=find(A1==90);
b=squeeze(phiVol(s,s,:));
plot(lwI,b);
title('\phi vs. l/w at \alpha_i=[90,90] from Volumetric data');
xlabel('l/w');ylabel('\phi');
%% plot a1 vs. a2 volumetric slices movie
fold = uigetdir('D:\RCMcode\RCM\Results\');
load([fold,'/phiVol.mat']);
% temp = [lw' ang1' ang2' phi'];
[x,y,z] = meshgrid(A1,A2,lwI);
v=phiVol;
mx=max(A1);
mn=min(A1);
mnl=min(lwI);
mxl=max(lwI);
for k = -0.5:.005:1.5
   hsp = surf(linspace(mn,mx,20),linspace(mn,mx,20),...
      zeros(20) + k);
   rotate(hsp,[1,-1,1],0)
   xd = hsp.XData;
   yd = hsp.YData;
   zd = hsp.ZData;
   delete(hsp)
   
   slice(x,y,z,v,[mnl,mxl],[],[mnl]) % Draw some volume boundaries
   hold on
   slice(x,y,z,v,xd,yd,zd)
   hold off
%    view(-5,10)
   drawnow
end
xlabel('\alpha_1');ylabel('\alpha_2');zlabel('l/w');