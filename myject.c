#include <pbc/pbc.h>
#include <pbc/pbc_test.h>
int main(int argc, char **argv) {
  pairing_t pairing;
  double t0, t1;
  element_t s,P,Ppub,Xa,Xb,Ya,Yb,xa,ya,ua,xb,yb,ub,k,t,K,T,h1,h2,h3,h4,h5,sig,temp1,temp2,temp3,Qa,Qb,temp4,temp5,temp6,temp7,temp8,temp9,temp10,option1,option2,option3,option4,option5,option6,option7,option8;
  pbc_demo_pairing_init(pairing, argc, argv);
  if (!pairing_is_symmetric(pairing)) pbc_die("pairing must be symmetric");
  element_init_Zr(s, pairing);
  element_init_Zr(k, pairing);
  element_init_Zr(t, pairing);
  element_init_Zr(xa, pairing);
  element_init_Zr(ya, pairing);
  element_init_Zr(ua, pairing);
  element_init_Zr(xb, pairing);
  element_init_Zr(yb, pairing);
  element_init_Zr(ub, pairing);
  
  
  element_init_G1(sig, pairing);
  element_init_G1(P, pairing);
  element_init_G1(Ppub, pairing);
  element_init_G1(T, pairing);
  element_init_G1(K, pairing);
  element_init_G1(Xa, pairing);
  element_init_G1(Xb, pairing);
  element_init_G1(Ya, pairing);
  element_init_G1(Yb, pairing);
  element_init_G1(h1, pairing);
  element_init_G1(h2, pairing);
  element_init_G1(h3, pairing);
  element_init_G1(h4, pairing);
  element_init_G1(h5, pairing);
  element_init_G1(temp1, pairing);
  element_init_G1(temp2, pairing);
  element_init_G1(temp3, pairing);
  element_init_G1(temp6, pairing);
  element_init_G1(temp7, pairing);
  element_init_G1(temp8, pairing);
  element_init_G1(temp9, pairing);
  element_init_G1(temp10, pairing);

  element_init_G1(Qa, pairing);
  element_init_G1(Qb, pairing);
  
  element_init_G1(temp4, pairing);
  element_init_G1(temp5, pairing);
  
  element_init_G1(option1, pairing);
  element_init_G1(option2, pairing);
  element_init_G1(option3, pairing);
  element_init_G1(option4, pairing);
  
   element_init_G1(option5, pairing);
  element_init_G1(option6, pairing);
   element_init_G1(option7, pairing);
  element_init_G1(option8, pairing);
  
   t0 = pbc_get_time();
  //首先经历setup阶段.
  printf("Setup Phase-----\n");
  
  element_random(P);
  element_printf("P = %B\n", P);
  element_random(s);
  element_mul_zn(Ppub, P, s);
  element_printf("Ppub = %B\n", Ppub);
  
  //KeyGen
  
  printf("EXTRACT STAGE\n");
  //发送者A注册.
  printf("A Register-----\n");
  element_random(xa);
  element_mul_zn(Xa,P,xa);
  element_random(ua);
  element_mul_zn(Ya,P,ua);
 // element_add(temp1,Xa,Ya);
  //element_from_hash(h1, "temp1", 5);
  //element_mul_zn(temp2,h1,s);
  //element_add(ya,ua,temp2);
  element_add(ya,ua,s);
  element_printf("Xa = %B\n", Xa);
  element_printf("Ya = %B\n", Ya);
  
  //接收者B注册.
  printf("B Register-----\n");
  
  element_random(xb);
  element_mul_zn(Xb,P,xb);
  element_random(ub);
  element_mul_zn(Yb,P,ub);
  //element_add(temp1,Xb,Yb);
 // element_from_hash(h1, "temp1", 5);
  //element_mul_zn(temp2,h1,s);
  //element_add(yb,ub,temp2);
  element_add(yb,ub,s);
  element_printf("Xb = %B\n", Xb);
  element_printf("Yb = %B\n", Yb);
  
  //发送消息
  printf("A send to B -----\n");
  
  element_random(k);
  element_random(t);
  
  element_mul_zn(K,P,k);
  element_mul_zn(T,P,t);
  element_add(temp3,Xb,Yb);
  //element_mul_zn(temp6,Ppub,h1);
 // element_add(temp7,temp6,temp3);
 element_add(temp7,Ppub,temp3);
  element_mul_zn(temp9,temp7,k);
  element_mul_zn(temp8,Xb,t);
  element_add(Qa,temp9,temp8);
  
  
  
  element_add(option1,option1,Xa);
  element_add(option1,option1,Xb);
  element_add(option1,option1,Ya);
  element_add(option1,option1,Yb);
  element_add(option1,option1,K);
  element_add(option1,option1,T);
  element_from_hash(h3, "option1", 7);
  element_from_hash(h4, "option1", 7);
  element_from_hash(h5, "option1", 7);
  
  element_mul_zn(option2,h3,t);
  
  element_mul_zn(option3,h4,xa);
  
  element_mul_zn(option4,h5,ya);
  
  element_add(option5,option3,option2);
  element_add(sig,option4,option5);
  
  element_printf("Qa = %B\n", Qa);
  element_printf("sig = %B\n", sig);
  element_printf("T = %B\n", T);
  element_printf("K = %B\n", K);
  
  
  
  //接收阶段
  printf("Decryption Phase -----\n");
  
  
 element_add(option6,xb,yb);
 element_mul_zn(option7,K,option6);
 

 element_mul_zn(option8,T,xb);
 
 element_add(Qb,option7,option8);
 
 element_printf("Qb = %B\n", Qb);
 
 if (element_cmp(Qa, Qb))
    printf("Decryption Success. Start session...\n");
  else
    printf("Decryption fail. Try again, please.\n");


//验证阶段
 printf("Verification Phase -----\n");
 
 
 element_mul_zn(temp4,P,sig);
 
 element_mul_zn(temp5,h3,T);
  
 element_mul_zn(temp6,h4,Xa);
   
 element_mul_zn(temp7,h5,Ya);
 
  element_mul_zn(temp8,h5,Ppub);
 
 element_add(option4,temp5,temp6);
 
 element_add(option4,option4,temp7);
  element_add(option4,option4,temp8);
 
 if (!element_cmp(temp4, option4))
    printf("Verify Success. Start session...\n");
  else
    printf("Verify fail. Try again, please.\n");

  element_clear(K);
  element_clear(T);
  element_clear(option1);
  element_clear(option2);
  element_clear(option3);
  element_clear(option4);
  element_clear(option5);
  element_clear(option6);
  element_clear(option7);
  element_clear(option8);
  
  element_clear(h1);
  element_clear(h2);
  element_clear(h3);
  element_clear(h4);
  element_clear(h5);
  element_clear(temp1);
  element_clear(temp2);
  element_clear(temp3);
  element_clear(temp4);
  element_clear(temp5);
   element_clear(temp6);
   element_clear(temp7); 
element_clear(temp8); 
element_clear(temp9);
 element_clear(temp10);
element_clear(Qa);
element_clear(Qb);
  element_clear(s);
  element_clear(xa);
  element_clear(xb);
   element_clear(ya);
  element_clear(yb);
   element_clear(ua);
  element_clear(ub);
  element_clear(P);
  element_clear(Ppub);
  element_clear(Xa);
  element_clear(Xb);
  element_clear(Ya);
  element_clear(Yb);
   element_clear(k);
  element_clear(t);
   element_clear(sig);
t1 = pbc_get_time();
 printf("All time = %fs\n", t1 - t0);
 printf("Have Good day.\n");

}
   