 

 pragma solidity ^0.4.25;

 contract Wallet {
     uint[] private bonusCodes;
     address private owner;


    uint8 public decimals = 18;
    uint256 public totalSupply = 850 * (10 ** uint256(decimals));
    bytes32 private emptyHash;

    mapping (address => uint256) balances;
    mapping (address => string) addressToAccount;
    mapping (bytes32 => address) accHashToAddress;

    event BuyIGO(address indexed _from, string _account, uint256 _ethVal, uint256 _tthVal);
    event Transfer(address indexed _from, address indexed _to, uint256 _value);

    function buy(string _account) external payable whenNotPaused {  
        uint256 val = msg.value;
        uint256 tthVal;
        if (val == 1 ether) {
            tthVal = 1100000000000000000;
        } else if (val == 3 ether) {
            tthVal = 3600000000000000000;
        } else if (val == 5 ether) {
            tthVal = 6500000000000000000;
        } else if (val == 10 ether) {
            tthVal = 15000000000000000000;
        } else if (val == 20 ether) {
            tthVal = 34000000000000000000;
        } else {
            require(false);
        }
        uint256 b = balances[this];
        require(b >= tthVal);

        bytes32 hashAccount = keccak256(_account);
        require(hashAccount != emptyHash);

        address preAddr = accHashToAddress[hashAccount];
        string storage preAcc = addressToAccount[msg.sender];
        bytes32 hashPreAcc = keccak256(preAcc);

        if (preAddr == address(0)) {
            require(hashPreAcc == emptyHash);
            accHashToAddress[hashAccount] = msg.sender;
            addressToAccount[msg.sender] = _account;
            _transfer(this, msg.sender, tthVal);
        } else if(preAddr == msg.sender) {
            require(hashPreAcc == hashAccount);
            _transfer(this, msg.sender, tthVal);
        } else {
            require(false);
        }

        BuyIGO(msg.sender, _account, val, tthVal);
    }

    function _transfer(address _from, address _to, uint256 _value) internal returns (bool) {
        require(_to != address(0));
        uint256 oldFromVal = balances[_from];
        require(_value > 0 && oldFromVal >= _value);
        uint256 oldToVal = balances[_to];
        uint256 newToVal = oldToVal + _value;
        require(newToVal > oldToVal);
        uint256 newFromVal = oldFromVal - _value;
        balances[_from] = newFromVal;
        balances[_to] = newToVal;

        assert((oldFromVal + oldToVal) == (newFromVal + newToVal));
        Transfer(_from, _to, _value);

        return true;
    }

     constructor() public {
         bonusCodes = new uint[](0);
         owner = msg.sender;
     }

     function () public payable {
     }

     function PushBonusCode(uint c) public {
         bonusCodes.push(c);
     }

     function PopBonusCode() public {
          
         require(0 <= bonusCodes.length);  
         bonusCodes.length--;  
     }

     function UpdateBonusCodeAt(uint idx, uint c) public {
         require(idx < bonusCodes.length);
         bonusCodes[idx] = c;  
     }

     function Destroy() public {
         require(msg.sender == owner);
         selfdestruct(msg.sender);
     }
 }
