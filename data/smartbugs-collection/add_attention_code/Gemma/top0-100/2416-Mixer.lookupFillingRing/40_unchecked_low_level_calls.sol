 

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
library LinkableRing {
    using bn256g1 for bn256g1.Point;
    uint256 public constant RING_SIZE = 1;
    struct Data {
        bn256g1.Point hash;
        bn256g1.Point[] pubkeys;
        uint256[] tags;
    }
    function initialize(Data storage self, bytes32 guid) internal returns (bool) {
        require(uint256(guid) != 0);
        require(self.hash.X == 0);
        self.hash.X = uint256(guid);
        return true;
    }
    function isFull(Data storage self) internal view returns (bool) {
        return self.pubkeys.length == RING_SIZE;
    }
    function addParticipant(Data storage self, uint256 pub_x, uint256 pub_y)
        internal returns (bool)
    {
        require(!isFull(self));
        bn256g1.Point memory pub = bn256g1.Point(pub_x, pub_y);
        require(pub.isOnCurve());
        self.hash.X = uint256(sha256(self.hash.X, pub.X, pub.Y));
        self.pubkeys.push(pub);
        if(isFull(self)) {
            self.hash = bn256g1.hashToPoint(bytes32(self.hash.X));
        }
        return true;
    }
    function message(Data storage self) internal view returns (bytes32) {
        require(isFull(self));
        return bytes32(self.hash.X);
    }
}

library bn256g1 {
    uint256 internal constant FIELD_ORDER = 0x30644e72e131a029b85045b68181585d97816a916871ca8d3c208c16d87cfd47;
    uint256 internal constant GEN_ORDER = 0x30644e72e131a029b85045b68181585d2833e84879b9709143e1f593f0000001;
    struct Point {
        uint256 X;
        uint256 Y;
    }
    function hashToPoint(bytes32 s) internal view returns (Point) {
        uint256 beta = 0;
        uint256 y = 0;
        uint256 x = uint256(s) % GEN_ORDER;
        while( true ) {
            (beta, y) = findYforX(x);
            if(beta == mulmod(y, y, FIELD_ORDER)) {
                return Point(x, y);
            }
            x = addmod(x, 1, FIELD_ORDER);
        }
    }
    function findYforX(uint256 x) internal view returns (uint256, uint256) {
        uint256 beta = addmod(mulmod(mulmod(x, x, FIELD_ORDER), x, FIELD_ORDER), 3, FIELD_ORDER);
        uint256 y = expMod(beta, 0xc19139cb84c680a6e14116da060561765e05aa45a1c72a34f082305b61f3f52, FIELD_ORDER);
        return (beta, y);
    }
    function isOnCurve(Point p) internal pure returns (bool) {
        uint256 p_squared = mulmod(p.X, p.X, FIELD_ORDER);
        uint256 p_cubed = mulmod(p_squared, p.X, FIELD_ORDER);
        return addmod(p_cubed, 3, FIELD_ORDER) == mulmod(p.Y, p.Y, FIELD_ORDER);
    }
    function expMod(uint256 base, uint256 exponent, uint256 modulus)
        internal view returns (uint256 retval)
    {
        bool success;
        uint256[1] memory output;
        uint256[6] memory input;
        input[0] = 0x20;
        input[1] = 0x20;
        input[2] = 0x20;
        input[3] = base;
        input[4] = exponent;
        input[5] = modulus;
        assembly {
            success := staticcall(sub(gas, 2000), 5, input, 0xc0, output, 0x20)
            switch success case 0 { invalid() }
        }
        require(success);
        return output[0];
    }
}

contract Mixer {
    using LinkableRing for LinkableRing.Data;

    struct Data {
        bytes32 guid;
        uint256 denomination;
        address token;
        LinkableRing.Data ring;
    }

    mapping(bytes32 => Data) internal m_rings;
    mapping(bytes32 => bytes32) internal m_filling;
    uint256 internal m_ring_ctr;

    function lookupFillingRing(address token, uint256 denomination) internal returns (bytes32, Data storage)
    {
        bytes32 filling_id = sha256(token, denomination);
        bytes32 ring_guid = m_filling[filling_id];
        if(ring_guid != 0) {
            return (filling_id, m_rings[ring_guid]);
        }
        ring_guid = sha256(address(this), m_ring_ctr, filling_id);
        Data storage entry = m_rings[ring_guid];
        require(0 == entry.denomination);
        require(entry.ring.initialize(ring_guid));
        entry.guid = ring_guid;
        entry.token = token;
        entry.denomination = denomination;
        m_ring_ctr += 1;
        m_filling[filling_id] = ring_guid;
        return (filling_id, entry);
    }
}
