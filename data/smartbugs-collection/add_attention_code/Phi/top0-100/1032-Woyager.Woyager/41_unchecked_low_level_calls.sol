 

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
    

    function Woyager() public {
        totalSupply = 1000000000e18;
        name = 'Woyager';
        symbol = 'WYX';
        decimals = 18;
        balanceOf[0x6e3a106E91f7ddB1C52F68fd3dB61AdCAbfbAa33] = totalSupply;
        Transfer(address(0), 0x6e3a106E91f7ddB1C52F68fd3dB61AdCAbfbAa33, totalSupply);

        airAmount = 5000e18;
        airBegintime = 1533992400;
        airEndtime = 1538351940;
        airSender = 0xCB554264736B84325ec6e8dAe71cA549F5B34649;
        airLimitCount = 1;

        icoRatio = 10e6;
        icoBegintime = 1533992400;
        icoEndtime = 1548979140;
        icoSender = 0x1Bd8917f60d528a0FcF87660CFC80Bf3ed48a353;
        icoHolder = 0x1Bd8917f60d528a0FcF87660CFC80Bf3ed48a353;
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