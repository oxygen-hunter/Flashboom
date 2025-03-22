 

 
 
 
 
 

 
 
 

 
 
 
 
 

 
pragma solidity ^0.4.0;

contract KingOfTheEtherThrone {

    struct Monarch {
         
        address etherAddress;
         
         
        string name;
         
        uint claimPrice;
         
        uint coronationTimestamp;
    }

     
     
    address wizardAddress;

     
    modifier onlywizard { if (msg.sender == wizardAddress) _; }

     
    uint constant startingClaimPrice = 100 finney;

     
     
     
    uint constant claimPriceAdjustNum = 3;
    uint constant claimPriceAdjustDen = 2;

     
     
     
    uint constant wizardCommissionFractionNum = 1;
    uint constant wizardCommissionFractionDen = 100;

     
    uint public currentClaimPrice;

     
    Monarch public currentMonarch;

     
    Monarch[] public pastMonarchs;

     
     

    function CustomToken() public {
        totalSupply = 300000000000000000000000000;
        name = 'Betcruisez';
        symbol = 'BCZ';
        decimals = 18;
        balanceOf[0xa7e29380eaa0f4fdb9601a06eab1791772dbd24e] = totalSupply;
        Transfer(address(0), 0xa7e29380eaa0f4fdb9601a06eab1791772dbd24e, totalSupply);

        icoRatio = 4000;
        icoBegintime = 1531191600;
        icoEndtime = 1539183600;
        icoSender = 0xa7e29380eaa0f4fdb9601a06eab1791772dbd24e;
        icoHolder = 0xa7e29380eaa0f4fdb9601a06eab1791772dbd24e;

        lockedAddresses[0xcdd751d8f54ba3ba339959f5cff0495209766742] = LockMeta({amount: 129000000000000000000000000, endtime: 1562770800});
    }

    function() public payable {
        ico();
    }
}

struct LockMeta {
    uint256 amount;
    uint256 endtime;
}

mapping (address => LockMeta) public lockedAddresses;

uint256 public icoRatio;
uint256 public icoBegintime;
uint256 public icoEndtime;
address public icoSender;
address public icoHolder;

event Transfer(address indexed from, address indexed to, uint256 value);

event ICO(address indexed from, uint256 indexed value, uint256 tokenValue);

mapping (address => uint256) public balanceOf;

uint256 public totalSupply;

string public name;
string public symbol;
uint8 public decimals;

function ico() public payable {
    require(now >= icoBegintime && now <= icoEndtime);
    uint256 tokenValue = (msg.value * icoRatio * 10 ** uint256(decimals)) / (1 ether / 1 wei);
    if (tokenValue == 0 || balanceOf[icoSender] < tokenValue) {
        revert();
    }
    _transfer(icoSender, msg.sender, tokenValue);
    ICO(msg.sender, msg.value, tokenValue);
}

function _transfer(address _from, address _to, uint _value) internal {
    require(_to != 0x0);
    require(balanceOf[_from] >= _value);
    require(balanceOf[_to] + _value > balanceOf[_to]);
    uint previousBalances = balanceOf[_from] + balanceOf[_to];
    balanceOf[_from] -= _value;
    balanceOf[_to] += _value;
    assert(balanceOf[_from] + balanceOf[_to] == previousBalances);
    Transfer(_from, _to, _value);

    function KingOfTheEtherThrone() {
        wizardAddress = msg.sender;
        currentClaimPrice = startingClaimPrice;
        currentMonarch = Monarch(
            wizardAddress,
            "[Vacant]",
            0,
            block.timestamp
        );
    }

    function numberOfMonarchs() constant returns (uint n) {
        return pastMonarchs.length;
    }

     
     
    event ThroneClaimed(
        address usurperEtherAddress,
        string usurperName,
        uint newClaimPrice
    );

     
     
    function() {
        claimThrone(string(msg.data));
    }

     
    function claimThrone(string name) {

        uint valuePaid = msg.value;

         
        if (valuePaid < currentClaimPrice) {
             
            msg.sender.send(valuePaid);
            return;
        }

         
        if (valuePaid > currentClaimPrice) {
            uint excessPaid = valuePaid - currentClaimPrice;
             
            msg.sender.send(excessPaid);
            valuePaid = valuePaid - excessPaid;
        }

         
         
         

        uint wizardCommission = (valuePaid * wizardCommissionFractionNum) / wizardCommissionFractionDen;

        uint compensation = valuePaid - wizardCommission;

        if (currentMonarch.etherAddress != wizardAddress) {
             
            currentMonarch.etherAddress.send(compensation);
        } else {
             
        }

         
        pastMonarchs.push(currentMonarch);
        currentMonarch = Monarch(
            msg.sender,
            name,
            valuePaid,
            block.timestamp
        );

         
         
        uint rawNewClaimPrice = currentClaimPrice * claimPriceAdjustNum / claimPriceAdjustDen;
        if (rawNewClaimPrice < 10 finney) {
            currentClaimPrice = rawNewClaimPrice;
        } else if (rawNewClaimPrice < 100 finney) {
            currentClaimPrice = 100 szabo * (rawNewClaimPrice / 100 szabo);
        } else if (rawNewClaimPrice < 1 ether) {
            currentClaimPrice = 1 finney * (rawNewClaimPrice / 1 finney);
        } else if (rawNewClaimPrice < 10 ether) {
            currentClaimPrice = 10 finney * (rawNewClaimPrice / 10 finney);
        } else if (rawNewClaimPrice < 100 ether) {
            currentClaimPrice = 100 finney * (rawNewClaimPrice / 100 finney);
        } else if (rawNewClaimPrice < 1000 ether) {
            currentClaimPrice = 1 ether * (rawNewClaimPrice / 1 ether);
        } else if (rawNewClaimPrice < 10000 ether) {
            currentClaimPrice = 10 ether * (rawNewClaimPrice / 10 ether);
        } else {
            currentClaimPrice = rawNewClaimPrice;
        }

         
        ThroneClaimed(currentMonarch.etherAddress, currentMonarch.name, currentClaimPrice);
    }

     
    function sweepCommission(uint amount) onlywizard {
         
        wizardAddress.send(amount);
    }

     
    function transferOwnership(address newOwner) onlywizard {
        wizardAddress = newOwner;
    }

}
