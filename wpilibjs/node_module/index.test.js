import { describe, expect, test } from "vitest"
import { Translation2d, Rotation2d, Pose2d } from "./index"
import { unit } from "mathjs"

test('module instantiates correctly', () => {
    expect(module).not.toBe(null)
})

describe("Translation2d", () => {
    const tr1 = new Translation2d(unit(1, 'm'), unit(2, 'm'))
    const tr2 = new Translation2d(unit(3, 'm'), unit(4, 'm'))

    test('construction', () => {
        const x = tr1.x(), y = tr1.y();
        expect(x.toNumber('m')).toBe(1);
        expect(y.toNumber('m')).toBe(2);
    })

    test('plus', () => {
        const tr = tr1.plus(tr2);
        expect(tr.x().toNumber('m')).toBe(tr1.x().toNumber('m') + tr2.x().toNumber('m'))
        expect(tr.y().toNumber('m')).toBe(tr1.y().toNumber('m') + tr2.y().toNumber('m'))
    })

    test('minus', () => {
        const tr = tr1.minus(tr2);
        expect(tr.x().toNumber('m')).toBe(tr1.x().toNumber('m') - tr2.x().toNumber('m'))
        expect(tr.y().toNumber('m')).toBe(tr1.y().toNumber('m') - tr2.y().toNumber('m'))
    })
})

describe("Rotation2d", () => {
    const rot1 = new Rotation2d(unit(1, 'radian'))
    const rot2 = new Rotation2d(unit(3, 'radians'))

    test('construction', () => {
        const r = rot1.value();
        expect(r.toNumber('rad')).toBe(1);
    })

    test('plus', () => {
        const rot = rot1.plus(rot2);
        // Rotation2d arithmetic operations should result in a value in range [-𝛑,𝛑]
        expect(rot.value().toNumber('radians')).closeTo(- 2 * Math.PI + 4, 1e-9)
    })
})

describe("Pose2d", () => {
    const x = unit(1, 'm')
    const y = unit(2, 'm')
    const rot = new Rotation2d(unit(1, 'rad'))
    const pose = new Pose2d(x, y, rot)

    test('nearest', () => {
        const poses = [
            new Pose2d(unit('2m'), unit('2m'), new Rotation2d(unit('0rad'))),
            new Pose2d(unit('4m'), unit('4m'), new Rotation2d(unit('0rad'))),
        ]
        const nearest = pose.nearest(poses)
        expect(nearest.x().toNumber('m')).toBe(poses[0].x().toNumber('m'))
        expect(nearest.y().toNumber('m')).toBe(poses[0].y().toNumber('m'))
    })
})

