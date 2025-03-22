 

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

library SafeMath {
  function mul(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a * b;
    assert(a == 0 || c / a == b);
    return c;
  }

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract EVCChain is StandardToken {

  string public constant name = "EVC Chain";
  string public constant symbol = "EVC";
  uint8 public constant decimals = 18;

  uint256 public constant INITIAL_SUPPLY = 1000000000 * (10 ** uint256(decimals));

  /**
   * @dev Constructor that gives msg.sender all of existing tokens.
   */
  function EVCChain() public {
    totalSupply = INITIAL_SUPPLY;

    //Investors 32%
    balances[0x5456118857653C15CFC5c42aFBA128eF198e2feB] = 320000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0x5456118857653C15CFC5c42aFBA128eF198e2feB, 320000000 * (10 ** uint256(decimals)));

    //Fundation 48% 
    balances[0xaa98eb0cb8389b118995aad028a28ca3f53923d3] = 480000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender,0xaa98eb0cb8389b118995aad028a28ca3f53923d3, 480000000 * (10 ** uint256(decimals)));

    //Core Team 20%
    balances[0x514D1A6BAE6D0d9f8879fd221F9702Ff511454Aa] = 200000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0x514D1A6BAE6D0d9f8879fd221F9702Ff511454Aa, 200000000 * (10 ** uint256(decimals)));
  }

}
