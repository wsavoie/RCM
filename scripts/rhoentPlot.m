%% plot a1 vs. a2 volumetric slices movie
fold = uigetdir('D:\RCMcode\RCM\Results\');
load([fold,'/phiVol.mat']);

% D=0.5;
alpha=2.648;
% temp = [lw' ang1' ang2' phi'];
figure(1)
for i=size(phiVol,3):-1:1
subplot(1,2,1)
phis=squeeze(phiVol(:,:,i));
Ls=squeeze(LVol(:,:,i));
Ws=squeeze(WVol(:,:,i));
Ds=squeeze(DVol(:,:,i));
vps=squeeze(vpVol(:,:,i));
surf(A1,A2,phis);

rhoent=(4*phis.^2/(pi*alpha)).*((Ls-Ds).*(Ws-2*Ds)./(Ds.^2.*vps));

xlabel('\alpha_1');ylabel('\alpha_2');zlabel('\rho_{ent}');
axis([-120,120,-120,120,.05,.3])
suptitle(['\rho_{ent} at L/W=',num2str(lwI(i))]);
subplot(1,2,2);
contour(A1,A2,rhoent);
xlabel('\alpha_1');ylabel('\alpha_2');
pause;
end