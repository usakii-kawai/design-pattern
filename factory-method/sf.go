package main

import "fmt"

// simple factory
type IGun interface {
	setName(name string)
	setPower(power int)
	getName() string
	getPower() int
}

// be composited
type Gun struct {
	name  string
	power int
}

func (g *Gun) setName(name string) { g.name = name }
func (g *Gun) setPower(power int)  { g.power = power }
func (g *Gun) getName() string     { return g.name }
func (g *Gun) getPower() int       { return g.power }

type Ak47 struct{ Gun }

func newAk47() IGun {
	return &Ak47{
		Gun: Gun{
			name:  "ak47",
			power: 4,
		},
	}
}

type Musket struct{ Gun }

func newMusket() IGun {
	return &Musket{
		Gun: Gun{
			name:  "musket",
			power: 4,
		},
	}
}

func getGun(gunType string) (IGun, error) {
	if gunType == "ak47" {
		return newAk47(), nil
	} else if gunType == "musket" {
		return newMusket(), nil
	}
	return nil, fmt.Errorf("wrong gun type passwd")
}

func showGun(g IGun) {
	fmt.Printf("{\n\tname: %s,\n\tpower: %d\n}\n", g.getName(), g.getPower())
}

func main() {
	ak, _ := getGun("ak47")
	ms, _ := getGun("musket")
	showGun(ak)
	showGun(ms)
}
