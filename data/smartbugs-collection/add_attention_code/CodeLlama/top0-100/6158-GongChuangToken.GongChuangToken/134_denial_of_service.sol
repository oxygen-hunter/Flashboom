 

pragma solidity ^0.4.25;

contract DosNumber {

    uint numElements = 0;
    uint[] array;

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

contract BaseToken {
    uint8 public decimals  = 18;
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
}

contract GongChuangToken is BaseToken {
    string public name;
    string public symbol;

    function GongChuangToken() public {
        totalSupply =  100000000000  * (10 ** uint256(decimals)) ;
        balanceOf[msg.sender] = totalSupply;
        name = 'GongChuangToken';
        symbol = 'GCT';
    }
}
