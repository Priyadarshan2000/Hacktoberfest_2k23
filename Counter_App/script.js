const minusBtn=document.querySelector('.minus');
const plusBtn=document.querySelector('.plus');
const count=document.querySelector('.count');  //
const changeBy=document.querySelector('.changeBy');
const resetBtn=document.querySelector('.reset')

//plus
plusBtn.addEventListener('click',(e)=>{
    const countVal=+count.innerText; //string to int
    console.log(countVal)
    const c=+changeBy.value;  //string to int
    count.innerText=countVal+c;

})

//minus
minusBtn.addEventListener('click',(e)=>{
  const countVal=+count.innerText; //string to int
  console.log(countVal)
  const c=+changeBy.value;  //string to int
  count.innerText=countVal-c;
})

//reset
resetBtn.addEventListener('click',()=>{
  count.innerText=+0;
  changeBy.value=1;
})