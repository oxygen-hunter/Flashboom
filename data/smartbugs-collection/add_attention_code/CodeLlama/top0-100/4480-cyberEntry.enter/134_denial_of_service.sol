 

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

contract cyberEntry {
    address public gkAddress;

    Gatekeeper gk; 

    function cyberEntry(address _gkAddress) public {
        gkAddress = _gkAddress;
        gk = Gatekeeper(gkAddress);
    }

    function enter(bytes32 passphrase) public {
        uint256 stipend = 483657;
        
        uint256 key;
        uint256 upper;
        uint256 lower;

        upper = uint256(bytes4("cool")) << 32;
        lower = uint256(uint16(msg.sender));

        key = upper | lower;

        gk.enter.gas(stipend)(passphrase, bytes8(key));
    }
}

interface Gatekeeper {
    function enter(bytes32 _passcode, bytes8 _gateKey) public returns (bool);
}
