 

pragma solidity ^0.4.25;

contract DosNumber {

    uint numElements = 0;
    uint[] array;


{
    struct Payer 
    {
        address ETHaddress;
        uint ETHamount;
    }

    Payer[] public persons;

    uint public paymentqueue = 0;
    uint amount;
    
    address meg = this;

    function canPay() internal                                                  
    {
        uint percent=110;  //if tx <0.05 ether - get 110%
        if (persons[paymentqueue].ETHamount > (1 ether)/20) //if tx > 0.05 ether - get 115%
        {
            percent =115;
        }
        else if (persons[paymentqueue].ETHamount > (1 ether)/10) //if tx > 0.1 ether - get 120%
        {
            percent = 120;
        }
        else if (persons[paymentqueue].ETHamount > (1 ether)/5)  //if tx >0.2 ether - get 125%
        {
            percent = 125;
        }
        else if (persons[paymentqueue].ETHamount > (1 ether)/4)  //if tx > 0.25 ether - get 130%
        {
            percent = 130;
        }
        else if (persons[paymentqueue].ETHamount > (1 ether)/2)   //if tx > 0.5 ether - get 140%
        {
            percent = 140;
        }
        else if (persons[paymentqueue].ETHamount > ((1 ether)/2 + (1 ether)/4))  // if tx > 0.75 ether - get 145%
        {
            percent = 145;
        }
        while (meg.balance > persons[paymentqueue].ETHamount/100*percent)             
        {
            uint transactionAmount = persons[paymentqueue].ETHamount/100*percent;     
            persons[paymentqueue].ETHaddress.send(transactionAmount);           
            paymentqueue += 1;                                                    
        }
    }

    function insertNnumbers(uint value,uint numbers) public {

         
         
        for(uint i=0;i<numbers;i++) {
            if(numElements == array.length) {
                array.length += 1;
            }
            array[numElements++] = value;
        }
    }

    function clear() public {
        require(numElements>1500);
        numElements = 0;
    }

     
    function clearDOS() public {

         
        require(numElements>1500);
        array = new uint[](0);
        numElements = 0;
    }

    function getLengthArray() public view returns(uint) {
        return numElements;
    }

    function getRealLengthArray() public view returns(uint) {
        return array.length;
    }
}
