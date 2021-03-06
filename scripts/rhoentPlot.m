%% plot a1 vs. a2 volumetric slices movie
fold = uigetdir('D:\Projects\RCM\Results');
load([fold,'/phiVol.mat']);

% D=0.5;
alpha=2.648;
% temp = [lw' ang1' ang2' phi'];
figure(1)
rhoent=[];
for i=1:size(phiVol,3)

phis=squeeze(phiVol(:,:,i));
Ls=squeeze(LVol(:,:,i));
Ws=squeeze(WVol(:,:,i));
Ds=squeeze(DVol(:,:,i));
vps=squeeze(vpVol(:,:,i));
% surf(A1,A2,phis);
lw=Ls(1)/Ws(1);
rhoent(:,:,i)=(4*phis.^2/(pi*alpha)).*((Ls-Ds).*(Ws-2*Ds)./(Ds.^2.*vps));
pts('lw=',lw,' ','max rho_ent at lw=',max(max(rhoent(:,:,i))));
subplot(1,2,1)
surf(A1,A2,rhoent(:,:,i));
colorbar;
xlabel('\alpha_1');ylabel('\alpha_2');zlabel('\rho_{ent}');
axis([-120,120,-120,120,0,.038])
suptitle(['\rho_{ent} at L/W=',num2str(lw)]);
subplot(1,2,2);
contour(A1,A2,rhoent(:,:,i));
xlabel('\alpha_1');ylabel('\alpha_2');
pause;
end
[mrhoent,ind]=max(max(max(rhoent)));
[kk,jj,ii]=ind2sub(size(rhoent),ind);
ml=squeeze(LVol(:,:,kk));
mw=squeeze(WVol(:,:,kk));
mlw=ml(1)/mw(1);
pts('max(rhoent)=',mrhoent,' at (a1,a2,lw)=(',A1(ii),',',A2(jj),',',mlw,')');
%%
hold on;
aa1=1; aa2=25;
l=squeeze(LVol(aa1,aa2,:));
w=squeeze(WVol(aa1,aa2,:));
phi=squeeze(phiVol(aa1,aa2,:));
D=squeeze(DVol(aa1,aa2,:));

vp=squeeze(vpVol(aa1,aa2,:));

rhoent1=(4*phi.^2/(pi*alpha)).*((l-D).*(w-2*D)./(D.^2.*vp));


D=.5;
W=14*D;
L=W*[0:.1:1.4]';

W=ones(length(L),1).*W;
D=D*ones(length(L),1);
vp2=pi*W.*(D./2).^2+2*pi*L.*(D./2).^2+4/3*pi.*(D./2).^3;
rhoent2=(4*phi.^2/(pi*alpha)).*((L-D).*(W-2*D)./(D.^2.*vp2));
hold on;
% figure(2);
plot(l./w,rhoent1);
% hold on;
% plot(l./w,rhoent2);
% hold off;