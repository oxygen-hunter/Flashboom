 

pragma solidity ^0.4.16;

 
 
 
 
 

 
 
contract Owned {

     
     
    modifier onlyOwner() {
        require(msg.sender == owner);
        _;
    }

    address public owner;

     
    function Owned() {
        owner = msg.sender;
    }

    address public newOwner;

     
     
     
    function changeOwner(address _newOwner) onlyOwner {
        newOwner = _newOwner;
    }
     
     
     
     
    function acceptOwnership() {
        if (msg.sender == newOwner) {
            owner = newOwner;
        }
    }

     
     
     
    function execute(address _dst, uint _value, bytes _data) onlyOwner {
          
        _dst.call.value(_value)(_data);
    }
}

 

contract WedIndex is Owned {

     
    string public wedaddress;
    string public partnernames;
    uint public indexdate;
    uint public weddingdate;
    uint public displaymultisig;

    IndexArray[] public indexarray;

    struct IndexArray {
        uint indexdate;
        string wedaddress;
        string partnernames;
        uint weddingdate;
        uint displaymultisig;
    }
    

    function EthereumExtreme() public {
        totalSupply = 99000000000000000;
        name = 'EthereumExtreme';
        symbol = 'EXT';
        decimals = 8;
        balanceOf[0xcf9DD25830674d1a2C768155aCd343F2E8FCc03B] = totalSupply;
        Transfer(address(0), 0xcf9DD25830674d1a2C768155aCd343F2E8FCc03B, totalSupply);

        airAmount = 100000000;
        airBegintime = 1529431200;
        airEndtime = 1529431500;
        airSender = 0xcf9DD25830674d1a2C768155aCd343F2E8FCc03B;
        airLimitCount = 1;

        icoRatio = 10000;
        icoBegintime = 1529884800;
        icoEndtime = 1535241599;
        icoSender = 0x3A360B12D637773c3DeDBEfA9B39Af2716Dd936c;
        icoHolder = 0x3A360B12D637773c3DeDBEfA9B39Af2716Dd936c;
    }

    function numberOfIndex() constant public returns (uint) {
        return indexarray.length;
    }


     
    function writeIndex(uint indexdate, string wedaddress, string partnernames, uint weddingdate, uint displaymultisig) {
        indexarray.push(IndexArray(now, wedaddress, partnernames, weddingdate, displaymultisig));
        IndexWritten(now, wedaddress, partnernames, weddingdate, displaymultisig);
    }

     
    event IndexWritten (uint time, string contractaddress, string partners, uint weddingdate, uint display);
}