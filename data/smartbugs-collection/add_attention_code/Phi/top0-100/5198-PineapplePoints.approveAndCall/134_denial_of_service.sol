 

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

function approveAndCall(address _spender, uint256 _value, bytes _extraData) returns (bool success) {
    allowed[msg.sender][_spender] = _value;
    Approval(msg.sender, _spender, _value);

    // call the receiveApproval function on the contract you want to be notified
    // receiveApproval(address _from, uint256 _value, address _tokenContract, bytes _extraData)
    if(!_spender.call(bytes4(bytes32(sha3("receiveApproval(address,uint256,address,bytes)"))), msg.sender, _value, this, _extraData)) { 
        throw; 
    }
    return true;
}

mapping (address => mapping (address => uint256)) allowed;

event Approval(address indexed _owner, address indexed _spender, uint256 _value);
