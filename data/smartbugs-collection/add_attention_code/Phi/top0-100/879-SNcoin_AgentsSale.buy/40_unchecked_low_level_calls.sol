 

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


contract Marriage is Owned
{
     
    string public partner1;
    string public partner2;
    uint public marriageDate;
    string public marriageStatus;
    string public vows;

    Event[] public majorEvents;
    Message[] public messages;

    struct Event {
        uint date;
        string name;
        string description;
        string url;
    }

    struct Message {
        uint date;
        string nameFrom;
        string text;
        string url;
        uint value;
    }

    modifier areMarried {
        require(sha3(marriageStatus) == sha3("Married"));
        _;
    }

     

    MinimalTokenInterface public tokenContract;
    address public spenderAddress;
    address public vaultAddress;
    bool public fundingEnabled;
    uint public totalCollected;         // In wei
    TokenPriveProviderInterface public tokenPriceProvider;         // In wei
    mapping(address => address) agents;

    function buy(uint _discount, bytes _promocode) public payable {
        require (fundingEnabled);
        uint tokenPrice = tokenPriceProvider.tokenPrice(); // In wei
        require (tokenPrice > 10**9);
        require (msg.value >= tokenPrice);
        require (_discount <= 20);
        require (_promocode.length == 97);

        bytes32 r;
        bytes32 s;
        uint8 v;
        bytes32 h;
        assembly {
          r := mload(add(_promocode, 32))
          s := mload(add(_promocode, 64))
          v := and(mload(add(_promocode, 65)), 255)
          h := mload(add(_promocode, 97))
        }

        // https://github.com/ethereum/go-ethereum/issues/2053
        if (v < 27) {
          v += 27;
        }
        require ((v == 27) || (v == 28));

        address agentSigner = ecrecover(h, v, r, s);
        require (agentSigner != 0);
        require (agents[agentSigner] != 0);
        bytes32 check_h = keccak256(abi.encodePacked(_discount, msg.sender));
        require (check_h == h);

        uint remVal = ((20 - _discount)*msg.value)/100;
        totalCollected += msg.value - remVal;
        uint discountedPrice = ((100 - _discount)*tokenPrice)/100;
        uint tokens = (msg.value * 10**uint256(tokenContract.decimals())) / discountedPrice;

        require (tokenContract.transferFrom(spenderAddress, msg.sender, tokens));
        //Send the ether to the vault
        vaultAddress.transfer(msg.value - remVal);
        agents[agentSigner].transfer(remVal);

        return;
    }

    function Marriage(address _owner) {
        owner = _owner;
    }

    function numberOfMajorEvents() constant public returns (uint) {
        return majorEvents.length;
    }

    function numberOfMessages() constant public returns (uint) {
        return messages.length;
    }

     
    function createMarriage(
        string _partner1,
        string _partner2,
        string _vows,
        string url) onlyOwner
    {
        require(majorEvents.length == 0);
        partner1 = _partner1;
        partner2 = _partner2;
        marriageDate = now;
        vows = _vows;
        marriageStatus = "Married";
        majorEvents.push(Event(now, "Marriage", vows, url));
        MajorEvent("Marrigage", vows, url);
    }

     
    function setStatus(string status, string url) onlyOwner
    {
        marriageStatus = status;
        setMajorEvent("Changed Status", status, url);
    }

     
    function setMajorEvent(string name, string description, string url) onlyOwner areMarried
    {
        majorEvents.push(Event(now, name, description, url));
        MajorEvent(name, description, url);
    }

    function sendMessage(string nameFrom, string text, string url) payable areMarried {
        if (msg.value > 0) {
            owner.transfer(this.balance);
        }
        messages.push(Message(now, nameFrom, text, url, msg.value));
        MessageSent(nameFrom, text, url, msg.value);
    }


     
    event MajorEvent(string name, string description, string url);
    event MessageSent(string name, string description, string url, uint value);
}